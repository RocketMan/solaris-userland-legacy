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

BUILD_BITS =            64_and_32
COMPILER=		gcc
BUILD_STYLE=		meson
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvdpau
COMPONENT_VERSION=	1.4
COMPONENT_PROJECT_URL=  http://freedesktop.org/wiki/Software/VDPAU/
COMPONENT_ARCHIVE_URL=	https://gitlab.freedesktop.org/vdpau/libvdpau/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:4258824c5a4555ef31de0a7d82b3caf19e75a16a13949f1edafc5f6fb2d33f30
COMPONENT_BUGDB=        x11/libraries
COMPONENT_ANITYA_ID=	1755
COMPONENT_BAID=		100273

include $(WS_MAKE_RULES)/x11-component.mk

MANIFEST_COMPARE=/usr/bin/true

# Documentation does not get reliably built anymore, so I am disabling it for
# now
CONFIGURE_OPTIONS += -Ddocumentation=false

# for tests
unexport SHELLOPTS
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libx11
