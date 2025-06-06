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
# Copyright (c) 2015, 2023, Oracle and/or its affiliates.
#

BUILD_BITS =            64_and_32
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gom
COMPONENT_VERSION=	0.4
# Below line containing COMPONENT_MAJOR_MINOR is added 
# so that gmake download does not fail during tarball download.
COMPONENT_MAJOR_MINOR=  $(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Gom
COMPONENT_ARCHIVE_HASH=	\
	sha256:68d08006aaa3b58169ce7cf1839498f45686fba8115f09acecb89d77e1018a9d
COMPONENT_BUGDB=        gnome/libraries
COMPONENT_ANITYA_ID=	13230

COMPONENT_BAID=		87254
BUILD_STYLE=		meson

include $(WS_MAKE_RULES)/gnome-component.mk

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

# Use explicit Python version rather than the default one
CONFIGURE_ENV +=	PYTHON=$(PYTHON.3.11)

# Assumes GNU xgettext in PATH.
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

$(SOLARIS_11_4_5_ONLY)CONFIGURE_OPTIONS += -Denable-gtk-doc=true
CONFIGURE_OPTIONS.32 += -Denable-introspection=false

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
