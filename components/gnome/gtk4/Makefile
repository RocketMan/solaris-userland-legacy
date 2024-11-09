#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2021, 2024, Oracle and/or its affiliates.
#

COMPILER =		gcc
BUILD_BITS =		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtk4
COMPONENT_VERSION=	4.16.5
COMPONENT_PROJECT_URL=	https://www.gtk.org/
COMPONENT_SRC=		gtk-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
    sha256:302d6813fbed95c419fb3ab67c5da5e214882b6a645c3eab9028dfb91ab418a4
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/gtk/4.16/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/gtk+
COMPONENT_ANITYA_ID=	13942

COMPONENT_BAID=		156481
BUILD_STYLE=		meson

include $(WS_MAKE_RULES)/gnome-component.mk
include $(WS_MAKE_RULES)/test-x11.mk

$(SOLARIS_11_3_ONLY)CFLAGS += -D_XPG6

COMPONENT_POST_UNPACK_ACTION += (cp $(COMPONENT_DIR)/files/fontify.c \
					$(SOURCE_DIR)/demos/gtk-demo ;\
				 mkdir bin ; \
				 ln -fs $(PYTHON) bin/python3)

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

CONFIGURE_OPTIONS += -Dwayland-backend=false
CONFIGURE_OPTIONS += -Dman-pages=true
CONFIGURE_OPTIONS += -Dintrospection=enabled
CONFIGURE_OPTIONS += -Dvulkan=disabled
# temporary until we upgrade gstreamer to 1.24.0 or later
CONFIGURE_OPTIONS += -Dmedia-gstreamer=disabled

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH64).master
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/Ok:/p" ' \
        '-e "/Fail:/p" ' \
        '-e "/Pass:/p" ' \
        '-e "/Skipped:/p" ' \
        '-e "/Timeout:/p" '

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng14
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/fribidi
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-bad
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-good
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-ugly
REQUIRED_PACKAGES += library/desktop/harfbuzz
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += media/ffmpeg
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
