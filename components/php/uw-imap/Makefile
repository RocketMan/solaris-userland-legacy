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
# Copyright (c) 2012, 2019, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64

# Parallel build jobs are supported only if GNU make is used.
COMPONENT_MAKE_JOBS=1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		imap
COMPONENT_VERSION=	2007f
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:53e15a2b5c1bc80161d42e9f69792a3fa18332b7b771910131004eb520004a28
COMPONENT_ARCHIVE_URL=	https://src.fedoraproject.org/lookaside/pkgs/uw-imap/imap-2007f.tar.gz/2126fd125ea26b73b20f01fcd5940369/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.washington.edu/imap/

BUILD_STYLE= justmake
include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(CPP_LARGEFILES)
# enable legacy stdio prototypes
# 7050600 sfw doesn't build on 166
CFLAGS += -D__USE_LEGACY_PROTOTYPES__
CFLAGS += -fPIC

COMPONENT_BUILD_TARGETS = soc c-client
COMPONENT_POST_BUILD_ACTION = ( \
	set -e; \
	$(MV) $(BUILD_DIR_64)/c-client/c-client.a \
		$(BUILD_DIR_64)/c-client/libc-client.a )
