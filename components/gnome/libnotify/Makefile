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
# Copyright (c) 2015, 2020, Oracle and/or its affiliates. 
#

BUILD_BITS = 64_and_32
COMPILER=gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libnotify
COMPONENT_VERSION=	0.7.7
COMPONENT_PROJECT_URL=	https://developer.gnome.org/libnotify/
COMPONENT_ARCHIVE_HASH=	\
	sha256:9cb4ce315b2655860c524d46b56010874214ec27e854086c1a1d0260137efc04
COMPONENT_BUGDB=        gnome/libraries
COMPONENT_ANITYA_ID=	13149

TPNO=			34499

# Build the old version for 11.3 compatibility.  We extract only the
# libnotify.so.1 libraries.
COMPONENT_VERSION_1=    0.5.2
COMPONENT_SRC_1=        $(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_MAJOR_MINOR_1=$(basename $(COMPONENT_VERSION_1))
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:ab6833e98c816ae96800de07c43c3a44015be64eb3f7f8117cdd0a0889e1f41d
COMPONENT_ARCHIVE_URL_1= \
    https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_MINOR_1)/$(COMPONENT_ARCHIVE_1)

BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)
INSTALL_OLD_DIR = $(PROTO_DIR)/$(COMPONENT_VERSION_1)
$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT=$(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_64)/.configured: CONFIGURE_SCRIPT=$(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured: BITS=32
$(BUILD_OLD_DIR_64)/.configured: BITS=64
$(BUILD_OLD_DIR_32)/.installed: COMPONENT_INSTALL_ARGS=DESTDIR=$(INSTALL_OLD_DIR)
$(BUILD_OLD_DIR_64)/.installed: COMPONENT_INSTALL_ARGS=DESTDIR=$(INSTALL_OLD_DIR)

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built
INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

# Tests do not work on Solaris yet
TEST_TARGET= $(SKIP_TEST)

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS.32 += --disable-introspection
CONFIGURE_OPTIONS.64 += --enable-introspection
CONFIGURE_OPTIONS += --disable-docbook-docs
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

# Required due to patches.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/documentation-tool/xmlto
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/libdbus-glib
