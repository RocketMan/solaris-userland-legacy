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
# Copyright (c) 2009, 2023, Oracle and/or its affiliates.
#

BUILD_BITS =		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		google-droid
COMPONENT_VERSION=	2013.06.07
# Add a 0. to the version from the tarball since this is a number we made up
# ourselves, and upstream may someday provide their own version number
IPS_COMPONENT_VERSION=	0.2013.6.7
COMPONENT_PROJECT_URL=	http://www.droidfonts.com/
COMPONENT_SRC=          $(COMPONENT_NAME)-fonts-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:61bb7b67050efcdbf5d434085c9cbe7570ed31d97a5ffa920401132bde0f07b1

# Download site for source
# Upstream doesn't have a stable download tarball, so we use our mirror
# to avoid having to git clone 2gb of Android source code for a handful
# of font files
COMPONENT_ARCHIVE_URL=	\
 https://github.com/oracle/solaris-xorg/releases/download/s12_25/$(COMPONENT_ARCHIVE)

COMPONENT_BUGDB=	x11/font
COMPONENT_BAID=		11324

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_FILES= 		*.ttf
COMPONENT_FONT_DOC_FILES= 	NOTICE *.txt

