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
# Copyright (c) 2017, 2023, Oracle and/or its affiliates.
#

BUILD_BITS=             NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bpg-georgian
COMPONENT_VERSION=	0.2009

# due to 27244651 the IPS version should be the solaris version
IPS_COMPONENT_VERSION=	$(PKG_SOLARIS_VERSION)

COMPONENT_SRC=		BPG_Fonts
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_PROJECT_URL=	http://bpgfonts.wordpress.com/category/gpl-gnu/

COMPONENT_ARCHIVE_URL=	https://onedrive.live.com/download.aspx?cid=2B325D7BF5367FE3&resid=2B325D7BF5367FE3%21461&ithint=%2Ezip
COMPONENT_ARCHIVE_HASH= \
    sha256:a18607dae0306b64ec3e814c0c91725a42d674b499848eeb33c5941222fa695d
COMPONENT_BUGDB=	g11n/font
COMPONENT_BAID=		10464

BUILD_STYLE=		archive
TEST_TARGET=		$(NO_TESTS)

# The zip doesn't unpack cleanly into its own directory.
UNPACK_ARGS= -r $(COMPONENT_SRC)

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_FILES= 		*.ttf
COMPONENT_FONT_DOC_FILES=	Docs/*.txt

COMPONENT_PREP_ACTION += \
	( cd $(@D); \
	  for fn in *.ttf; do $(MV) "$$fn" "$${fn%_GPL&GNU.ttf}.ttf"; done; );
