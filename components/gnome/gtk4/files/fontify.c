#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#include <gtk/gtk.h>
#include <glib/gstdio.h>

/* Stupid syntax highlighting.
 *
 * No regex was used in the making of this highlighting.
 * It should only work for simple cases.  This is good, as
 * that's all we should have in the demos.
 */
/* This code should not be used elsewhere, except perhaps as an example of how
 * to iterate through a text buffer.
 */
enum {
  STATE_NORMAL,
  STATE_IN_COMMENT
};

static gchar *tokens[] =
{
  "/*",
  "\"",
  NULL
};

static gchar *types[] =
{
  "static",
  "const ",
  "void",
  "gint",
  " int ",
  " char ",
  "gchar ",
  "gfloat",
  "float",
  "double",
  "gint8",
  "gint16",
  "gint32",
  "guint",
  "guint8",
  "guint16",
  "guint32",
  "guchar",
  "glong",
  "gboolean" ,
  "gshort",
  "gushort",
  "gulong",
  "gdouble",
  "gldouble",
  "gpointer",
  "NULL",
  "GList",
  "GSList",
  "FALSE",
  "TRUE",
  "FILE ",
  "GtkColorSelection ",
  "GtkWidget ",
  "GtkButton ",
  "GdkColor ",
  "GdkRectangle ",
  "GdkEventExpose ",
  "GdkGC ",
  "GdkPixbufLoader ",
  "GdkPixbuf ",
  "GError",
  "size_t",
  "GtkAboutDialog ",
  "GtkAction ",
  "GtkActionEntry ",
  "GtkRadioActionEntry ",
  "GtkIconFactory ",
  "GtkIconSet ",
  "GtkTextBuffer ",
  "GtkStatusbar ",
  "GtkTextIter ",
  "GtkTextMark ",
  "GdkEventWindowState ",
  "GtkActionGroup ",
  "GtkUIManager ",
  "GtkRadioAction ",
  "GtkActionClass ",
  "GtkToggleActionEntry ",
  "GtkAssistant ",
  "GtkBuilder ",
  "GtkSizeGroup ",
  "GtkTreeModel ",
  "GtkTreeSelection ",
  "GdkDisplay ",
  "GdkScreen ",
  "GdkWindow ",
  "GdkEventButton ",
  "GdkCursor ",
  "GtkTreeIter ",
  "GtkTreeViewColumn ",
  "GdkDisplayManager ",
  "GtkClipboard ",
  "GtkIconSize ",
  "GtkImage ",
  "GdkDragContext ",
  "GtkSelectionData ",
  "GtkDialog ",
  "GtkMenuItem ",
  "GtkListStore ",
  "GtkCellLayout ",
  "GtkCellRenderer ",
  "GtkTreePath ",
  "GtkTreeStore ",
  "GtkEntry ",
  "GtkEditable ",
  "GtkEditableInterface ",
  "GdkPixmap ",
  "GdkEventConfigure ",
  "GdkEventMotion ",
  "GdkModifierType ",
  "GtkEntryCompletion ",
  "GtkToolItem ",
  "GDir ",
  "GtkIconView ",
  "GtkCellRendererText ",
  "GtkContainer ",
  "GtkAccelGroup ",
  "GtkPaned ",
  "GtkPrintOperation ",
  "GtkPrintContext ",
  "cairo_t ",
  "PangoLayout "
  "PangoFontDescription ",
  "PangoRenderer ",
  "PangoMatrix ",
  "PangoContext ",
  "PangoLayout ",
  "GtkTable ",
  "GtkToggleButton ",
  "GString ",
  "GtkIconSize ",
  "GtkTreeView ",
  "GtkTextTag ",
  "GdkEvent ",
  "GdkEventKey ",
  "GtkTextView ",
  "GdkEventVisibility ",
  "GdkBitmap ",
  "GtkTextChildAnchor ",
  "GArray ",
  "GtkCellEditable ",
  "GtkCellRendererToggle ",
  NULL
};

static gchar *control[] =
{
  " if ",
  " while ",
  " else",
  " do ",
  " for ",
  "?",
  ":",
  "return ",
  "goto ",
  NULL
};
void
parse_chars (gchar     *text,
             gchar    **end_ptr,
             gint      *state,
             gchar    **tag,
             gboolean   start)
{
  gint i;
  gchar *next_token;

  /* Handle comments first */
  if (*state == STATE_IN_COMMENT)
    {
      *end_ptr = strstr (text, "*/");
      if (*end_ptr)
        {
          *end_ptr += 2;
          *state = STATE_NORMAL;
          *tag = "comment";
        }
      return;
    }

  *tag = NULL;
  *end_ptr = NULL;

  /* check for comment */
  if (!strncmp (text, "/*", 2))
    {
      *end_ptr = strstr (text, "*/");
      if (*end_ptr)
        *end_ptr += 2;
      else
        *state = STATE_IN_COMMENT;
      *tag = "comment";
      return;
    }

  /* check for preprocessor defines */
  if (*text == '#' && start)
    {
      *end_ptr = NULL;
      *tag = "preprocessor";
      return;
    }

  /* functions */
  if (start && * text != '\t' && *text != ' ' && *text != '{' && *text != '}')
    {
      if (strstr (text, "("))
        {
          *end_ptr = strstr (text, "(");
          *tag = "function";
          return;
        }
    }
  /* check for types */
  for (i = 0; types[i] != NULL; i++)
    if (!strncmp (text, types[i], strlen (types[i])) ||
        (start && types[i][0] == ' ' && !strncmp (text, types[i] + 1, strlen (types[i]) - 1)))
      {
        *end_ptr = text + strlen (types[i]);
        *tag = "type";
        return;
      }

  /* check for control */
  for (i = 0; control[i] != NULL; i++)
    if (!strncmp (text, control[i], strlen (control[i])))
      {
        *end_ptr = text + strlen (control[i]);
        *tag = "control";
        return;
      }

  /* check for string */
  if (text[0] == '"')
    {
      gint maybe_escape = FALSE;

      *end_ptr = text + 1;
      *tag = "string";
      while (**end_ptr != '\000')
        {
          if (**end_ptr == '\"' && !maybe_escape)
            {
              *end_ptr += 1;
              return;
            }
          if (**end_ptr == '\\')
            maybe_escape = TRUE;
          else
            maybe_escape = FALSE;
          *end_ptr += 1;
        }
      return;
    }

  /* not at the start of a tag.  Find the next one. */
  for (i = 0; tokens[i] != NULL; i++)
    {
      next_token = strstr (text, tokens[i]);
      if (next_token)
        {
          if (*end_ptr)
            *end_ptr = (*end_ptr<next_token)?*end_ptr:next_token;
          else
            *end_ptr = next_token;
        }
    }

  for (i = 0; types[i] != NULL; i++)
    {
      next_token = strstr (text, types[i]);
      if (next_token)
        {
          if (*end_ptr)
            *end_ptr = (*end_ptr<next_token)?*end_ptr:next_token;
          else
            *end_ptr = next_token;
        }
    }

  for (i = 0; control[i] != NULL; i++)
    {
      next_token = strstr (text, control[i]);
      if (next_token)
        {
          if (*end_ptr)
            *end_ptr = (*end_ptr<next_token)?*end_ptr:next_token;
          else
            *end_ptr = next_token;
        }
    }
}

/* While not as cool as c-mode, this will do as a quick attempt at highlighting */
void
fontify (const char *format, GtkTextBuffer *source_buffer)
{
  GtkTextIter start_iter, next_iter, tmp_iter;
  gint state;
  gchar *text;
  gchar *start_ptr, *end_ptr;
  gchar *tag;

  gtk_text_buffer_create_tag (source_buffer, "source",
                              "font", "monospace",
                              NULL);
  gtk_text_buffer_create_tag (source_buffer, "comment",
                              "foreground", "DodgerBlue",
                              NULL);
  gtk_text_buffer_create_tag (source_buffer, "type",
                              "foreground", "ForestGreen",
                              NULL);
  gtk_text_buffer_create_tag (source_buffer, "string",
                              "foreground", "RosyBrown",
                              "weight", PANGO_WEIGHT_BOLD,
                              NULL);
  gtk_text_buffer_create_tag (source_buffer, "control",
                              "foreground", "purple",
                              NULL);
  gtk_text_buffer_create_tag (source_buffer, "preprocessor",
                              "style", PANGO_STYLE_OBLIQUE,
                              "foreground", "burlywood4",
                              NULL);
  gtk_text_buffer_create_tag (source_buffer, "function",
                              "weight", PANGO_WEIGHT_BOLD,
                              "foreground", "DarkGoldenrod4",
                              NULL);

  gtk_text_buffer_get_bounds (source_buffer, &start_iter, &tmp_iter);
  gtk_text_buffer_apply_tag_by_name (source_buffer, "source", &start_iter, &tmp_iter);

  state = STATE_NORMAL;

  gtk_text_buffer_get_iter_at_offset (source_buffer, &start_iter, 0);

  next_iter = start_iter;
  while (gtk_text_iter_forward_line (&next_iter))
    {
      gboolean start = TRUE;
      start_ptr = text = gtk_text_iter_get_text (&start_iter, &next_iter);

      do
        {
          parse_chars (start_ptr, &end_ptr, &state, &tag, start);

          start = FALSE;
          if (end_ptr)
            {
              tmp_iter = start_iter;
              gtk_text_iter_forward_chars (&tmp_iter, end_ptr - start_ptr);
            }
          else
            {
              tmp_iter = next_iter;
            }
          if (tag)
            gtk_text_buffer_apply_tag_by_name (source_buffer, tag, &start_iter, &tmp_iter);

          start_iter = tmp_iter;
          start_ptr = end_ptr;
        }
      while (end_ptr);

      g_free (text);
      start_iter = next_iter;
    }
}
