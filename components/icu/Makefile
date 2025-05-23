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
# Copyright (c) 2018, 2021, Oracle and/or its affiliates.
#
BUILD_BITS= 64_and_32

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		icu4c
COMPONENT_VERSION=	71_1
IPS_COMPONENT_VERSION=	71.1
PLATNUM=		2
HUMAN_VERSION=		$(COMPONENT_VERSION)-1
COMPONENT_PROJECT_URL=  http://site.icu-project.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tgz
COMPONENT_ARCHIVE_HASH= \
	sha256:67a7e6e51f61faf1306b6935333e13b2c48abd8da6d2f46ce6adca24b1e21ebf
COMPONENT_ARCHIVE_URL=  https://github.com/unicode-org/icu/releases/download/release-71-1/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	library/icu
COMPONENT_ANITYA_ID=	16134

COMPONENT_BAID=		106181

# OpenPGP Key obtained from https://ssl.icu-project.org/KEYS

# set relocate_to option while unpacking the tar ball
UNPACK_ARGS= -r $(COMPONENT_SRC)

COMPONENT_BUILD_TARGETS = all

# use version of gcc/g++ specified in the gate
PATH=$(GCC_ROOT)/bin:$(GNUBIN):$(USRBINDIR)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_SCRIPT = $(SOURCE_DIR)/icu/source/runConfigureICU Solaris/clang

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-data-packaging=library
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-samples
CONFIGURE_OPTIONS += --disable-renaming

COMPILER = gcc

CFLAGS += -D__EXTENSIONS__ -DDECCHECK -U_XOPEN_SOURCE -D_XOPEN_SOURCE=600 -D_STDC_C99
CXXFLAGS += -D__EXTENSIONS__ -DDECCHECK -U_XOPEN_SOURCE -D_XOPEN_SOURCE=600 -D_STDC_C99 -std=c++11

include ../../make-rules/shared-targets.mk

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^All tests OK:  testdata intltest iotest cintltst/p" ' \
	'-e "/^PASS: config selfcheck OK/p" '

REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/llvm/clang-c++-runtime
REQUIRED_PACKAGES += system/library/math
