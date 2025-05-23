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

BUILD_BITS= 64_and_32
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER= gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		at-spi2-core
COMPONENT_VERSION=	2.40.3
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Accessibility
COMPONENT_ARCHIVE_HASH=	\
    sha256:e49837c2ad30d71e1f29ca8e0968a54b95030272f7ff40b89b48968653f37a5c
COMPONENT_BUGDB=	gnome/a11y-libs-core
COMPONENT_ANITYA_ID=	7841

COMPONENT_BAID=		106963
BUILD_STYLE=		meson

# Tests do not work on Solaris yet
TEST_TARGET= $(SKIP_TEST)

include $(WS_MAKE_RULES)/gnome-component.mk

CPPFLAGS += -D_XOPEN_SOURCE=700 -D__EXTENSIONS__ -D_XPG6

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

COMPONENT_INSTALL_ENV += PATH="$(GNUBIN):$(PATH)"
CONFIGURE_OPTIONS += -Ddbus_daemon=$(USRLIBDIR)/dbus-daemon
CONFIGURE_OPTIONS += -Dintrospection=yes
CONFIGURE_OPTIONS += -Db_pie=false

COMPONENT_POST_INSTALL_ACTION.64 += \
        $(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/at-spi-registryd.1 \
                $(PROTO_DIR)/usr/share/man/man1/at-spi-registryd.1;

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/server/xorg
