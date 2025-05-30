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
# Copyright (c) 2020, 2023, Oracle and/or its affiliates.
#

BUILD_BITS =		64
COMPILER =		gcc
include ../../../make-rules/shared-macros.mk
GCC_ROOT =		/usr/gcc/10

COMPONENT_NAME=		libhandy
COMPONENT_VERSION=	1.8.0
COMPONENT_PROJECT_URL=	https://gitlab.gnome.org/GNOME/libhandy
COMPONENT_ARCHIVE_HASH=	\
	sha256:6c2542c0578924b0c29b7ae6cb44eb26df38eb01d6d5ef3d7d0b0825763230e8
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	114486

COMPONENT_BAID=		130748
BUILD_STYLE=		meson

MANIFEST_COMPARE=	/usr/bin/true

include $(WS_MAKE_RULES)/gnome-component.mk
include $(WS_MAKE_RULES)/test-x11.mk

CONFIGURE_OPTIONS.32 += -Dintrospection=disabled
CONFIGURE_OPTIONS.64 += -Dintrospection=enabled
CONFIGURE_OPTIONS += -Dexamples=false

$(SOLARIS_11_4_5_ONLY)CFLAGS += -Wstack-protector -fdata-sections -fstack-protector-all
$(SOLARIS_11_3_ONLY)CFLAGS += -Wno-stack-protector

# Version 1.0.2 requires following for GCC 11 build.
CFLAGS += -Wno-error=incompatible-pointer-types

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_INSTALL_ENV += PATH="$(GNUBIN):$(PATH)"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += developer/ui-designer/glade
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/fribidi
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
