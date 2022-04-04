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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		help2man
COMPONENT_VERSION=	1.49.1
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fd99a664ec4be9a86a0dd89719989f14f367a9c079d75d0e1d71e18a7bb51b03
COMPONENT_ARCHIVE_URL=	http://mirror.team-cymru.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1309

COMPONENT_BAID=		119701

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_ENV +=	PERL=$(PERL)

# Needed to successfully create the message files.
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

# Needed to get all the localized files.
COMPONENT_INSTALL_TARGETS += install_l10n

REQUIRED_PACKAGES += $(PERL_PKG)
