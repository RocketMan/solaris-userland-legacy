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

COMPONENT_NAME=		gjs
COMPONENT_VERSION=	1.70.2
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Gjs
COMPONENT_ARCHIVE_HASH= \
	sha256:5dd661910d38a6ccd5b75c09ea83319ac16ad06236b537e555415a70610015b0
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	9532

COMPONENT_BAID=		118904
BUILD_STYLE=		meson

# Tests do not work in Solaris yet
TEST_TARGET = $(SKIP_TEST)

include $(WS_MAKE_RULES)/gnome-component.mk

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

# This section is workaround for 35310697
ifeq ($(MACH), sparc)
# Temporary workaround to build and link gobject-introspection against older libffi
# Make sure that libffi is installed first
$(CONFIGURE_64): ../../libffi/build/$(MACH64)/.installed

../../libffi/build/$(MACH64)/.installed:
	$(MAKE) -C ../../libffi install

# Create custom libffi.pc
COMPONENT_PRE_CONFIGURE_ACTION += cp $(COMPONENT_DIR)/files/libffi.pc $(COMPONENT_DIR)/build;
COMPONENT_PRE_CONFIGURE_ACTION += perl -pi -e 's,PREFIX,$(WS_TOP)/components/libffi/build/3.2.1-$(MACH64),' $(COMPONENT_DIR)/build/libffi.pc;
# And point pkg-config to it
PKG_CONFIG_PATH=$(COMPONENT_DIR)/build:/usr/lib/$(MACH64)/pkgconfig
# Fix runtime path
COMPONENT_POST_INSTALL_ACTION += \
        $(ELFEDIT) -e "dyn:rpath \$$ORIGIN/../../.." ./build/$(MACH64)/installed-tests/js/libgjstesttools/libgjstesttools.so; \
        $(ELFEDIT) -e "dyn:runpath \$$ORIGIN/../../.." ./build/$(MACH64)/installed-tests/js/libgjstesttools/libgjstesttools.so; \
        $(ELFEDIT) -e "dyn:delete RUNPATH" -e "dyn:delete RPATH" ./build/$(MACH64)/libgjs.so;
# Just double check that we link to correct library
COMPONENT_POST_BUILD_ACTION += \
        LIBFFI=`find $(COMPONENT_DIR) -name \*.so | xargs elfdump -d | grep NEEDED | grep libffi.so.6`; \
        if [ -z "$$LIBFFI" ]; then \
            echo "Error, this library should be linked to libffi.so.6, is libffi built?"; \
            exit 1; \
        fi
endif

CXXFLAGS += -std=c++17

CONFIGURE_OPTIONS += -Dcairo=enabled
CONFIGURE_OPTIONS += -Dprofiler=disabled
# we don't need to distribute gjs tests
CONFIGURE_OPTIONS += -Dinstalled_tests=false

# Workaround the mozjs issue described in 24935318
ifeq ($(MACH), sparc)
LD_EXEC_OPTIONS.64 += -M $(WS_COMPONENTS)/desktop/polkit/mapfile
COMPONENT_BUILD_ENV.64 += LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS.64)"
COMPONENT_INSTALL_ENV.64 += LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS.64)"
endif

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libmozjs-78
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
