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

COMPONENT_NAME=		mod_qos
COMPONENT_VERSION=	11.76
COMPONENT_PROJECT_URL=	https://mod-qos.sourceforge.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:f317bf01e4f459e1e2d4949e2578ad0d5cd97744ae79fd65522ce7df83b543fc
COMPONENT_ARCHIVE_FILE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= \
    https://sourceforge.net/projects/mod-qos/files/$(COMPONENT_ARCHIVE_FILE)/download
COMPONENT_BUGDB=	utility/apache
COMPONENT_ANITYA_ID=	1999

BUILD_STYLE=justmake

MODULES_INSTALL=
MODULES_TEST= $(TEST_AND_COMPARE_64)

include ../modules.mk

APACHE_MODULE_SRC= mod_qos.c
APACHE_MODULE_LDFLAGS= -lcrypto
APACHE_MODULE_SUBDIR= apache2

include ../apache_module.mk

REQUIRED_PACKAGES += library/security/openssl
