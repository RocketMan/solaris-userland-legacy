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
# Copyright (c) 2025 Jim Mason <jmason at ibinx doc com>.
#
# Adapted from original code Copyright (c) 2011, 2023, Oracle and/or its
# affiliates.
#

BUILD_BITS= 64
COMPILER=clang
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_evasive
COMPONENT_VERSION=	2.4.0
COMPONENT_PROJECT_URL=	https://github.com/jvdmr/mod_evasive
COMPONENT_ARCHIVE_HASH=	\
    sha256:1d55dd6005c3aaa95f75c555c7d7f555992a1cf849a93fd2fd6cdfd32ac9ccac
COMPONENT_ARCHIVE_FILE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= \
    https://github.com/jvdmr/mod_evasive/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=	utility/apache

BUILD_STYLE=justmake

MODULES_INSTALL=
MODULES_TEST= $(TEST_AND_COMPARE_64)

include ../modules.mk

COMPONENT_PREP_ACTION += \
	$(CP) files/build.mk $(@D)/Makefile
