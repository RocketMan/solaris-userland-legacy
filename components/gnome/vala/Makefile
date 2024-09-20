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

BUILD_BITS = 64
COMPILER=gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vala
COMPONENT_VERSION=	0.56.17
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Vala
COMPONENT_ARCHIVE_HASH= \
	sha256:26100c4e4ef0049c619275f140d97cf565883d00c7543c82bcce5a426934ed6a
COMPONENT_BUGDB=        gnome/dev-tools
COMPONENT_ANITYA_ID=	5065

COMPONENT_BAID=		110824

# 23285126 - vala integrated tests should be hooked up
TEST_TARGET= $(SKIP_TEST)

include $(WS_MAKE_RULES)/gnome-component.mk

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += developer/graphviz
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += library/glib2
