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
# Copyright (c) 2011, 2023, Oracle and/or its affiliates.
#
BUILD_BITS= 64
# Because the Studio compiler generates thousands of lines of warnings.
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		links
COMPONENT_VERSION=	2.28
COMPONENT_BAID=		131741
COMPONENT_ARCHIVE_HASH=	sha256:b20bcac4817e338a91653fad1ba062cf4416d7107a146aade3cb7a9d46e0c370
COMPONENT_PROJECT_URL=	http://links.twibright.com/
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1822

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL =		0

# Without this, linker flags from pkgconfig are added too late to take effect
LDFLAGS += -L/usr/openssl/3/lib/64
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"

CONFIGURE_OPTIONS +=	--with-ssl=/usr/openssl/3

# Configure in links does not understand CC, CXX, etc.  Need to generate a
# new configure for it to configure and build properly.
COMPONENT_PREP_ACTION=	(cd $(@D) ; autoconf)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += library/security/openssl-3
REQUIRED_PACKAGES += library/zlib
