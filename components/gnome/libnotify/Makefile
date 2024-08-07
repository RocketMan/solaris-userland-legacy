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

BUILD_BITS = 64_and_32
COMPILER=gcc
include ../../../make-rules/shared-macros.mk
BUILD_STYLE=		meson

COMPONENT_NAME=		libnotify
COMPONENT_VERSION=	0.7.12
COMPONENT_PROJECT_URL=	https://developer.gnome.org/libnotify/
COMPONENT_ARCHIVE_HASH=	\
	sha256:744b2b37508135f8261b755a9debe6e09add421adc75bde930f6e198b70ab46e
COMPONENT_BUGDB=        gnome/libraries
COMPONENT_ANITYA_ID=	13149

COMPONENT_BAID=		123942

MANIFEST_COMPARE=	/usr/bin/true

# Tests do not work on Solaris yet
TEST_TARGET= $(SKIP_TEST)

include $(WS_MAKE_RULES)/gnome-component.mk

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

# Required for other components.
CONFIGURE_OPTIONS.32 += -Dintrospection=disabled
CONFIGURE_OPTIONS.64 += -Dintrospection=enabled

CONFIGURE_OPTIONS += -Dman=false
CONFIGURE_OPTIONS += -Dgtk_doc=false
CONFIGURE_OPTIONS += -Ddocbook-docs=false
CONFIGURE_OPTIONS += -Ddefault_library=shared

# Build the old version for 11.3 compatibility.
PRE_CLEAN_ACTION += gmake -C $(COMPONENT_DIR)/legacy clean;
COMPONENT_PRE_CONFIGURE_ACTION += gmake -C $(COMPONENT_DIR)/legacy build;
COMPONENT_PRE_INSTALL_ACTION += gmake -C $(COMPONENT_DIR)/legacy install;

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/documentation-tool/xmlto
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/libdbus-glib
