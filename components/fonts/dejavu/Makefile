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
# Copyright (c) 2007, 2023, Oracle and/or its affiliates.
#

BUILD_BITS =		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dejavu
COMPONENT_VERSION=	2.37
COMPONENT_PROJECT_URL= 	https://dejavu-fonts.github.io/
COMPONENT_SRC=          $(COMPONENT_NAME)-fonts-ttf-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:fa9ca4d13871dd122f61258a80d01751d603b4d3ee14095d65453b4e846e17d7
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/dejavu/dejavu/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	x11/font
COMPONENT_ANITYA_ID=	418
COMPONENT_BAID= 	34239

TEST_TARGET= $(NO_TESTS)

COMPONENT_FONT_SRC_DIR=		ttf
COMPONENT_FONT_FILES= 		*.ttf

COMPONENT_FONT_DOC_FILES= 	LICENSE *.txt

COMPONENT_FONT_CONF_SRC_DIR= 	fontconfig
COMPONENT_FONT_CONF_FILES=	*.conf

include $(WS_MAKE_RULES)/font.mk

# Generate README file
COMPONENT_POST_INSTALL_ACTION += \
	grep -v travis-ci.org $(SOURCE_DIR)/README.md > \
		$(PROTO_DIR)$(COMPONENT_FONT_DOC_DEST_DIR)/README ;
