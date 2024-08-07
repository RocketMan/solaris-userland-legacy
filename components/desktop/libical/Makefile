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

BUILD_BITS=		64_and_32
# For now, all things built for C++11 require gcc.
COMPILER= 		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libical
COMPONENT_VERSION=	3.0.16
COMPONENT_PROJECT_URL=	http://libical.github.io/libical/
COMPONENT_ARCHIVE_HASH= \
	sha256:b44705dd71ca4538c86fb16248483ab4b48978524fb1da5097bd76aa2e0f0c33
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	1637
COMPONENT_BAID=		133528

# Build the old version for 11.3 compatibility.  We extract only the
# libical.so.0 libraries
COMPONENT_VERSION_1=	0.48
COMPONENT_SRC_1=	libical-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:8bfdf66e4bfa2f16ac33e0d4671cdddd5d76d06076c0bea8ba9a09508f7291e1
COMPONENT_ARCHIVE_URL_1= \
    https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION_1).tar.gz

BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)
INSTALL_OLD_DIR = $(PROTO_DIR)/$(COMPONENT_VERSION_1)

$(BUILD_OLD_DIR_32)/.built: SOURCE_DIR = $(SOURCE_DIR_1)
$(BUILD_OLD_DIR_32)/.built: COMPONENT_SRC = $(COMPONENT_SRC_1)
$(BUILD_OLD_DIR_64)/.built: BITS=64
$(BUILD_OLD_DIR_64)/.built: SOURCE_DIR = $(SOURCE_DIR_1)
$(BUILD_OLD_DIR_64)/.built: COMPONENT_SRC = $(COMPONENT_SRC_1)
$(BUILD_OLD_DIR_32)/.installed: COMPONENT_INSTALL_ARGS = DESTDIR=$(INSTALL_OLD_DIR)
$(BUILD_OLD_DIR_64)/.installed: COMPONENT_INSTALL_ARGS = DESTDIR=$(INSTALL_OLD_DIR)

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

BUILD_STYLE= cmake

# Tests do not pass because of insufficient gsed filtering.
$(SKIP_TEST_AT_TOP_LEVEL)

include $(WS_MAKE_RULES)/common.mk

# The Makefile of this component does not support multiple build jobs.
COMPONENT_MAKE_JOBS=1 

# Use project's own optimisation flags instead.
gcc_OPT=

# Requires __EXTENSIONS__ for access to various non-standard time functions.
CFLAGS += -D__EXTENSIONS__
CXXFLAGS += -std=c++11 -D__EXTENSIONS__

CMAKE_OPTIONS += -DSHARED_ONLY=true
# Required for other components.
CMAKE_OPTIONS.32 += -DGOBJECT_INTROSPECTION=false
CMAKE_OPTIONS.64 += -DGOBJECT_INTROSPECTION=true
# Always use Solaris-provided timezone data.
CMAKE_OPTIONS += -DUSE_BUILTIN_TZDATA=false
CMAKE_OPTIONS.32 += -DICAL_GLIB=false
CMAKE_OPTIONS.64 += -DICAL_GLIB=true
CMAKE_OPTIONS.64 += -DICAL_GLIB_VAPI=true

#CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON

# Workaround g-ir-scanner breakage.
LD_Z_IGNORE=

# Required for gobject-introspection invocation.
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CXX="$(CXX)"
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS).master
COMPONENT_TEST_TARGETS = test

# Remove any color coding from the test output.
COMPONENT_TEST_ARGS += COLOR=no

# Enable libadimalloc or libumem (only ADI caught the heap-use-after-free case)
ISA_EXTENSIONS.64	= $(shell isainfo -x | grep '^$(MACH64):')
TEST_MEMCHECK_ENV.32	= LD_PRELOAD=libumem.so UMEM_DEBUG=default,verbose
ifeq ($(filter adi, $(ISA_EXTENSIONS.64)), adi)
TEST_MEMCHECK_ENV.64	= LD_PRELOAD_64=libadimalloc.so.1
TEST_MEMCHECK_ENV.64	+= ADIMALLOC_DEBUG=default,verbose,adi_precise
else
TEST_MEMCHECK_ENV.64	= $(TEST_MEMCHECK_ENV.32)
endif
TEST_MEMCHECK_ENV	= $(TEST_MEMCHECK_ENV.$(BITS))

COMPONENT_POST_INSTALL_ACTION.64 += \
        $(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/libical.3lib \
                $(PROTO_DIR)/usr/share/man/man3lib/libical.3lib; \
        $(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/libicalss.3lib \
                $(PROTO_DIR)/usr/share/man/man3lib/libicalss.3lib; \
        $(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/libicalvcal.3lib \
                $(PROTO_DIR)/usr/share/man/man3lib/libicalvcal.3lib;

# Check upstream test case from https://github.com/libical/libical/issues/253
COMPONENT_POST_TEST_ACTION += \
	(cd $(COMPONENT_TEST_DIR) ; \
	  printf 'Extra Test: parser-heap-use-after-free ...........   ' ; \
	  $(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) $(TEST_MEMCHECK_ENV) \
	  ./src/test/parser \
	  $(COMPONENT_DIR)/files/test-data/heap-use-after-free.ics \
	  >> /dev/null && print 'Passed' ) &>> $(COMPONENT_TEST_OUTPUT)

# Remove time measurements from results when comparing
COMPONENT_TEST_TRANSFORMS += '-e "s|  *[\.0-9]* sec||g" '

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
