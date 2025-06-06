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
# Copyright (c) 2015, 2023, Oracle and/or its affiliates.
#

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		eog-plugins
COMPONENT_VERSION=	3.26.7
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/EyeOfGnome
COMPONENT_ARCHIVE_HASH= \
	sha256:2ce6c19e29eb723e2362a8b0d9c396e686d065e17acfc584cc8c2b0949a17b3d
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.26/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/applications
COMPONENT_ANITYA_ID=	13120

COMPONENT_BAID=		113010

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/gnome-component.mk

# Set runpath to find libeog.so library.
LDFLAGS += -Wl,-R$(USRLIBDIR64)/eog

# Assumes GNU msgfmt is in PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
CONFIGURE_ENV += PYTHON=$(PYTHON.3.11)
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --with-cms
CONFIGURE_OPTIONS += --with-libexif
CONFIGURE_OPTIONS += --with-libjpeg
CONFIGURE_OPTIONS += --with-librsvg
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --with-xmp

REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/viewer/eog
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libchamplain
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/exempi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/desktop/libpeas
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
