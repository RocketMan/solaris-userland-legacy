## libadwaita

This port of libadwaita largely follows upstream, except that it respects
the chosen system theme, thus making it behave like a `libhandy` for gtk4.

Stock libadwaita, as the name suggests, substitutes its own, in-built Adwaita
theme in place of the current system theme.  This port uses the system theme;
it will use the in-built theme only if the system theme is Adwaita.

### Screenshots

Using [slim-nimbus](https://github.com/RocketMan/solaris-ports/tree/master/components/look-and-feel/slim-nimbus):
![screenshot](https://raw.githubusercontent.com/RocketMan/solaris-userland-legacy/refs/heads/master/components/gnome/libadwaita/screenshot.png "libadwaita 1.3.6")

