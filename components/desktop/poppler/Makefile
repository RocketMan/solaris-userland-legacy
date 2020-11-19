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
# Copyright (c) 2016, 2020, Oracle and/or its affiliates.
#
BUILD_BITS= 64_and_32
COMPILER=gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		poppler
COMPONENT_VERSION=	20.10.0
COMPONENT_PROJECT_URL=	https://poppler.freedesktop.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:434ecbbb539c1a75955030a1c9b24c7b58200b7f68d2e4269e29acf2f8f13336
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/poppler
COMPONENT_ANITYA_ID=	3686
TPNO_POPPLER=		62723

COMPONENT_NAME_1=	poppler-data
COMPONENT_VERSION_1=	0.4.9
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:1f9c7e7de9ecd0db6ab287349e31bf815ca108a5a175cf906a90163bdbe32012
COMPONENT_ARCHIVE_URL_1= $(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE_1)
COMPONENT_ANITYA_ID_1=	3687
TPNO_POPPLER_DATA=	46916

# Only cmake is currently supported to build libpoppler.
BUILD_STYLE = cmake

# Build the old version for 11.3 compatibility.  We extract only the
# libpoppler-glib.so.5 and libpoppler.so.7 libraries.
COMPONENT_VERSION_2=	0.14.5
COMPONENT_SRC_2=	poppler-$(COMPONENT_VERSION_2)
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_HASH_2= \
    sha256:c805317c4c1a7080098ae8c7c2a1c1b8e2c784858fc2e04941878eeb8164814c
COMPONENT_ARCHIVE_URL_2= \
    https://poppler.freedesktop.org/$(COMPONENT_ARCHIVE_2)

SOURCE_DIR_2 = $(COMPONENT_DIR)/$(COMPONENT_SRC_2)
BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_2)-$(MACH32)
INSTALL_OLD_DIR = $(PROTO_DIR)/$(COMPONENT_VERSION_2)
PATCH_OLD_DIR = patches_$(COMPONENT_VERSION_2)

PATCHES_OLD := $(wildcard $(PATCH_OLD_DIR)/*.patch)
PATCHES_OLD_STAMPS = $(PATCHES_OLD:$(PATCH_OLD_DIR)/%=$(SOURCE_DIR_2)/.patched-%)

# this is the configure environment for the SOURCE_DIR_2 build
CONFIGURE_ENV = CONFIG_SHELL="$(CONFIG_SHELL)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CXX="$(CXX)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"

# configure options for the SOURCE_DIR_2 build
CONFIGURE_PREFIX = /usr
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_PREFIX)/share/man
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_PREFIX)/bin
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_PREFIX)/sbin
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_PREFIX)/lib

$(SOURCE_DIR_2)/.patched-%:	$(PATCH_OLD_DIR)/%
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $<
	$(TOUCH) $(@)

$(SOURCE_DIR_2)/.patched:	$(SOURCE_DIR_2)/.unpacked $(PATCHES_OLD_STAMPS)
	$(TOUCH) $(@)

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT=$(SOURCE_DIR_2)/configure
$(BUILD_OLD_DIR_32)/.configured: COMPILER=studio
$(BUILD_OLD_DIR_32)/.configured: BITS=32
$(BUILD_OLD_DIR_32)/.configured: CXX+=$(studio_NORUNPATH)
$(BUILD_OLD_DIR_32)/.configured: CXXFLAGS=$(CXXFLAGS.studio)
$(BUILD_OLD_DIR_32)/.configured: $(SOURCE_DIR_2)/.patched
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
		$(CONFIGURE_SCRIPT) $(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

$(BUILD_OLD_DIR_32)/.built: COMPONENT_PRE_BUILD_ACTION=
$(BUILD_OLD_DIR_32)/.built: COMPONENT_POST_BUILD_ACTION=
$(BUILD_OLD_DIR_32)/.built: $(BUILD_OLD_DIR_32)/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(@D)
endif
	$(TOUCH) $@

$(BUILD_OLD_DIR_32)/.installed: COMPONENT_INSTALL_ARGS=DESTDIR=$(INSTALL_OLD_DIR)

BUILD_32 += $(SOURCE_DIR_2)/.patched $(BUILD_OLD_DIR_32)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

MANIFEST_COMPARE=/usr/bin/true

# The path to cmake configure file has to be specified explicitly,
# otherwise 32-bit openjpeg library is attempted to be linked to 64-bit 
OPENJPEG_CMAKE_DIR = $(shell pkg-config --modversion libopenjp2 | \
                       perl -F'\.' -nae 'print "openjpeg-$$F[0].$$F[1]"')
CMAKE_OPTIONS.32 += -DOpenJPEG_DIR=/usr/lib/cmake/$(OPENJPEG_CMAKE_DIR)
CMAKE_OPTIONS.64 += -DOpenJPEG_DIR=/usr/lib/$(MACH64)/cmake/$(OPENJPEG_CMAKE_DIR)

# Reduce build time dependencies since we don't ship this
# or can't run it as an automated test.
CMAKE_OPTIONS += -DBUILD_CPP_TESTS=OFF
CMAKE_OPTIONS += -DBUILD_GTK_TESTS=OFF
CMAKE_OPTIONS += -DBUILD_QT5_TESTS=OFF

# Build shared libpoppler libraries.
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

# Not necessary for the userland consolidation.
CMAKE_OPTIONS += -DENABLE_ZLIB=OFF
CMAKE_OPTIONS += -DENABLE_QT5=OFF

# Required by other components.
CMAKE_OPTIONS += -DWITH_Cairo=ON
CMAKE_OPTIONS += -DWITH_Iconv=ON
CMAKE_OPTIONS += -DWITH_GLIB=ON
CMAKE_OPTIONS += -DWITH_GTK=ON
CMAKE_OPTIONS += -DWITH_NSS3=ON
CMAKE_OPTIONS += -DWITH_JPEG=ON
CMAKE_OPTIONS += -DWITH_PNG=ON
CMAKE_OPTIONS += -DWITH_TIFF=ON
CMAKE_OPTIONS.32 += -DWITH_GObjectIntrospection=OFF
CMAKE_OPTIONS.64 += -DWITH_GObjectIntrospection=ON
CMAKE_OPTIONS += -DENABLE_UNSTABLE_API_ABI_HEADERS=ON

# Install the poppler data files.
COMPONENT_POST_BUILD_ACTION = \
	(cd $(COMPONENT_DIR)/$(COMPONENT_SRC_1); \
	$(GMAKE) prefix=$(CONFIGURE_PREFIX) DESTDIR=$(PROTO_DIR) install)
#	$(GMAKE) prefix=/usr DESTDIR=$(PROTO_DIR) install)

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS += V=1

##PKG_OBJ =	poppler
##SUBPKG_OBJ =	poppler-desktop
##EXCLUSION_FILE = poppler-desktop-deps
##
##include $(WS_MAKE_RULES)/pkgobjs.mk
##$(EXCLUSION_FILE_TARGET): $(HEAP_OBJ)
##	find $(PROTO_DIR) -type f | (while read f; do file "$$f"; done) | grep -w ELF | cut -f1 -d\: | (while read f; do echo $$f: `ldd "$$f"`; done) | egrep 'libXrender|gobj|libX11|glib|libGL' | cut -f1 -d\: | sed -e 's$$$(PROTO_DIR)/$$$$' | sed -e 's/$(MACH64)/$$(MACH64)/' > $@.tmp ; \
##	find $(PROTO_DIR) -type f | egrep 'cairo' | sed -e 's$$$(PROTO_DIR)/$$$$' | sed -e 's/$(MACH64)/$$(MACH64)/' >> $@.tmp ; \
##	find $(PROTO_DIR) -type f -o -type l | egrep 'glib|gir|g-i-r' | sed -e 's$$$(PROTO_DIR)/$$$$' | sed -e 's/$(MACH64)/$$(MACH64)/' >> $@.tmp ; \
##	sort -u $@.tmp > $@ ; \
##	rm $@.tmp

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libpng14
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg2
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/security/nss
REQUIRED_PACKAGES += print/filter/poppler
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/libc
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
