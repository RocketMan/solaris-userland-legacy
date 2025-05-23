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
# Copyright (c) 2015, 2022, Oracle and/or its affiliates.
#

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		eog
COMPONENT_VERSION=	41.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/EyeOfGnome
COMPONENT_ARCHIVE_HASH= \
	sha256:917de086fd97fd3ec930fa07c88badd2be1f5d0ae6b9e569c986004e0359a9ac
COMPONENT_BUGDB=	gnome/applications
COMPONENT_ANITYA_ID=	5393

COMPONENT_BAID=		108921
BUILD_STYLE=		meson

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/gnome-component.mk

# Assumes GNU msgfmt is in PATH.
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(GNUBIN):$(PATH)

CONFIGURE_OPTIONS += -Dlibportal=false

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

CFLAGS += $(CPP_XPG6MODE)
$(SOLARIS_11_3_ONLY)LDFLAGS += -ljpeg

COMPONENT_POST_INSTALL_ACTION += \
        $(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/eog.1 \
                $(PROTO_DIR)/usr/share/man/man1/eog.1;

# Temporary workaround until all build machines are running meson-0.63
COMPONENT_POST_INSTALL_ACTION += \
for f in $(PROTO_DIR)/usr/share/help/[a-z]*/eog/figures ; do \
    (cd $$f ; $(RM) *.png ; $(SYMLINK) ../../../C/eog/figures/*.png . ); \
done ;

REQUIRED_PACKAGES += data/shared-mime-info
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/viewer/eog/eog-plugins
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/exempi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/desktop/libpeas
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
