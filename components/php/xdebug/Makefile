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
BUILD_BITS= 64
COMPILER= gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdebug
COMPONENT_VERSION=	3.2.0
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
	sha256:7769b20eecdadf5fbe9f582512c10b394fb575b6f7a8c3a3a82db6883e0032b7
COMPONENT_ARCHIVE_URL=	http://xdebug.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://xdebug.org/
COMPONENT_BUGDB=	utility/php
COMPONENT_ANITYA_ID=	13302

COMPONENT_BAID=		136038

TEST_TARGET= $(NO_TESTS)
include $(PHP_TOP_DIR)/phpize.mk
include $(WS_MAKE_RULES)/common.mk
include $(PHP_TOP_DIR)/php.mk

CONFIGURE_OPTIONS +=	--enable-xdebug

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/php-74
REQUIRED_PACKAGES += web/php-80
REQUIRED_PACKAGES += web/php-81
REQUIRED_PACKAGES += web/php-82
