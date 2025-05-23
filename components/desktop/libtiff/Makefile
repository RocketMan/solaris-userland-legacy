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
# Copyright (c) 2015, 2023, Oracle and/or its affiliates.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtiff
COMPONENT_VERSION=	4.4.0
COMPONENT_PROJECT_URL=	http://www.simplesystems.org/libtiff/
COMPONENT_SRC=		tiff-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:917223b37538959aca3b790d2d73aa6e626b688e02dcda272aec24c2f498abed
COMPONENT_ARCHIVE_URL=	http://download.osgeo.org/libtiff/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libtiff
COMPONENT_ANITYA_ID=	1738

COMPONENT_BAID=		128730

# Build the old version for 11.3 compatibility.  We extract only the
# libtiff.so.3 libraries
COMPONENT_VERSION_1=	3.9.5
COMPONENT_SRC_1=	tiff-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:ecf2e30582698dbc61d269203bbd1e701a1a50fb26c87d709e10d89669badb33
COMPONENT_ARCHIVE_URL_1= \
    http://download.osgeo.org/libtiff/old/$(COMPONENT_ARCHIVE_1)

BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)
INSTALL_OLD_DIR = $(PROTO_DIR)/$(COMPONENT_VERSION_1)

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured: BITS=32
$(BUILD_OLD_DIR_64)/.configured: BITS=64
$(BUILD_OLD_DIR_32)/.installed: COMPONENT_INSTALL_ARGS = DESTDIR=$(INSTALL_OLD_DIR)
$(BUILD_OLD_DIR_64)/.installed: COMPONENT_INSTALL_ARGS = DESTDIR=$(INSTALL_OLD_DIR)

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

# Added to find the *.3tiff that go into /usr/share/man/man3tiff
PKG_PROTO_DIRS += $(COMPONENT_SRC)/man
PKG_PROTO_DIRS += $(INSTALL_OLD_DIR)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

MANIFEST_COMPARE=/usr/bin/true

CC 			+= $(CC_BITS)

# Only build C library, not C++ library
CONFIGURE_OPTIONS       += --disable-cxx
# Only build shared library, not static libraries
CONFIGURE_OPTIONS       += --enable-shared --disable-static
# Don't build tiffgt utility which drags in a pile of OpenGL dependencies
CONFIGURE_OPTIONS       += ax_cv_check_gl_libgl="no"
CONFIGURE_OPTIONS       += CXXFLAGS='$(CXXFLAGS)'
CONFIGURE_OPTIONS       += CFLAGS='$(CFLAGS)'

# Tests need GNU version of diff to work correctly
COMPONENT_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TARGETS	= check
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/result_count/d" ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

configure:	$(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64) $(BUILD_DIR)/.merged-header

test:           $(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

$(BUILD_DIR)/.merged-header: $(BUILD_DIR_32)/.installed $(BUILD_DIR_64)/.installed
	-$(RM) $(PROTO_DIR)/usr/include/tiffconf.h
	$(GDIFF) -D _LP64 \
            $(BUILD_DIR_32)/libtiff/tiffconf.h $(BUILD_DIR_64)/libtiff/tiffconf.h \
            > $(PROTO_DIR)/usr/include/tiffconf.h; \
	diffstatus=$$? ; \
	if (( $$diffstatus != 1 )) ; then exit $$diffstatus ; fi

REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libwebp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math

