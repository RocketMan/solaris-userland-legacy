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
# Copyright (c) 2018, 2023, Oracle and/or its affiliates.
#

BUILD_BITS =            32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xorgproto
COMPONENT_VERSION=	2021.5
COMPONENT_CATEGORY=	proto
COMPONENT_ARCHIVE_HASH= \
	sha256:aa2f663b8dbd632960b24f7477aa07d901210057f6ab1a1db5158732569ca015
COMPONENT_BUGDB=        x11/libraries
COMPONENT_ANITYA_ID=	17190
COMPONENT_BAID=		109914

# sun-ext-protos just delivers headers and xcb-proto is part of libxcb

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files/sun-ext-protos/include

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/x11-component.mk

COMPONENT_PREP_ACTION +=(cd $(@D); $(AUTORECONF_ENV) autoreconf -fiv);

COMPONENT_INSTALL_ARGS += pkgconfigdir="$(DESTDIR)/usr/share/pkgconfig"
CONFIGURE_ENV += XORG_SGML_PATH="$(PROTO_DIR)/usr/share/sgml"

# We've either EOF'ed or never shipped support for all the legacy extensions
CONFIGURE_OPTIONS += --disable-legacy

REQUIRED_PACKAGES += developer/documentation-tool/asciidoc
REQUIRED_PACKAGES += x11/documentation/xorg-docs
