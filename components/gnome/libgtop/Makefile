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
# Copyright (c) 2015, 2018, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            32_and_64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgtop
COMPONENT_VERSION=	2.36.0
COMPONENT_PROJECT_URL=	https://developer.gnome.org/libgtop/
COMPONENT_ARCHIVE_HASH=	\
	sha256:13bfe34c150b2b00b03df4732e8c7ccfae09ab15897ee4f4ebf0d16b0f3ba12b
COMPONENT_BUGDB=        gnome/libraries
COMPONENT_ANITYA_ID=	13146

TPNO=			34656

# Build the old version for 11.3 compatibility.  We extract only the
# libgtop-2.0.so.7 libraries
COMPONENT_VERSION_1=	2.28.2
COMPONENT_MAJOR_MINOR=  $(basename $(COMPONENT_VERSION_1))
COMPONENT_SRC_1=	libgtop-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:f32d65d5e18976439479fef51e94972dd849ce4b8aed8f7ac14a8f43bb094bf1
COMPONENT_ARCHIVE_URL_1= \
    https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_MINOR)/$(COMPONENT_ARCHIVE_1)

SOURCE_DIR_1 = $(COMPONENT_DIR)/$(COMPONENT_SRC_1)
BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
INSTALL_OLD_DIR = $(PROTO_DIR)/$(COMPONENT_VERSION_1)
PATCH_DIR_1 = patches_1
PATCHES_1 := $(wildcard $(PATCH_DIR_1)/*.patch)
PATCH_STAMPS_1 = $(PATCHES_1:$(PATCH_DIR_1)/%=$(SOURCE_DIR_1)/.patched-%)

$(SOURCE_DIR_1)/.patched-%: $(PATCH_DIR_1)/%
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $<
	$(TOUCH) $(@)

$(SOURCE_DIR_1)/.patched: $(SOURCE_DIR_1)/.unpacked $(PATCH_STAMPS_1)
	$(TOUCH) $(@)

$(SOURCE_DIR_1)/.prep: $(SOURCE_DIR_1)/.patched
	$(COMPONENT_PREP_ACTION)
	$(TOUCH) $@

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured: BITS=32
$(BUILD_OLD_DIR_32)/.installed: COMPONENT_INSTALL_ARGS = DESTDIR=$(INSTALL_OLD_DIR)

BUILD_32 += $(SOURCE_DIR_1)/.prep $(BUILD_OLD_DIR_32)/.built
INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/gnome-component.mk

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --enable-gtk-doc

# Required due to patches.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += x11/library/libxau
