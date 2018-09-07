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
# Copyright (c) 2010, 2018, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtasn1
COMPONENT_VERSION=	4.13
COMPONENT_ARCHIVE_HASH= \
    sha256:ff8072dd30d73c87f717b5940275bacd390b31794a2c890e51c010b71e319c16
COMPONENT_BUGDB=	library/libtasn1
COMPONENT_ANITYA_ID=	1734
COMPONENT_SIG_URL=

TPNO=			40971

# Build the old version for 11.3 compatibility.  We extract only the
# libtasn1.so.3 libraries.
COMPONENT_VERSION_1=    2.8
COMPONENT_SRC_1=        $(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:2b7d74f4b10b18ae2f0291fcafabe30e42c9ededdea41add8c622302132d545a
COMPONENT_ARCHIVE_URL_1= \
    https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE_1)

BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
INSTALL_OLD_DIR = $(PROTO_DIR)/$(COMPONENT_VERSION_1)
$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured: BITS=32
$(BUILD_OLD_DIR_32)/.installed: COMPONENT_INSTALL_ARGS = DESTDIR=$(INSTALL_OLD_DIR)

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed

COMPONENT_BUILD_TARGETS = all info

include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --includedir=$(CONFIGURE_INCLUDEDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

include ../../make-rules/shared-targets.mk

TEST_TARGET:	install

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-n -e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/All/p" '

