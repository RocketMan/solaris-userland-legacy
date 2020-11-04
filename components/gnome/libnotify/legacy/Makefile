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
# Copyright (c) 2015, 2020, Oracle and/or its affiliates. 
#

BUILD_BITS = 64_and_32
COMPILER=gcc
include ../../../../make-rules/shared-macros.mk

# Build the old version for 11.3 compatibility.  We extract only the
# libnotify.so.1 libraries.
COMPONENT_NAME=		libnotify
COMPONENT_VERSION=	0.5.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_MAJOR_MINOR=	$(basename $(COMPONENT_VERSION))
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ab6833e98c816ae96800de07c43c3a44015be64eb3f7f8117cdd0a0889e1f41d
COMPONENT_ARCHIVE_URL=	\
    https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_MINOR)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS.32 += --disable-introspection
CONFIGURE_OPTIONS.64 += --enable-introspection
CONFIGURE_OPTIONS += --disable-docbook-docs
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
