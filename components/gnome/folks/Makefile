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

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		folks
COMPONENT_VERSION=	0.15.5
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Folks
COMPONENT_ARCHIVE_HASH= \
	sha256:0fff8a896330cd82aee4598324f7e541c884d0337536212723b4beb38c759086
COMPONENT_BUGDB=        gnome/libraries
COMPONENT_ANITYA_ID=	13121

COMPONENT_BAID=		139055
BUILD_STYLE=            meson

include $(WS_MAKE_RULES)/gnome-component.mk

# __EXTENSIONS__ required for various non-standard function usages.
CFLAGS += -D__EXTENSIONS__
# Not compiled as an xpg6 application, but configure defines this, so we
# override and undefine it to avoid feature_tests.h failures; unclear what the
# correct fix is.
CFLAGS += -U_POSIX_SOURCE

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_INSTALL_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_TEST_ENV += PATH="$(USRLIBDIR):$(PATH)"
COMPONENT_TEST_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# bluetooth support (unnecessary)
CONFIGURE_OPTIONS += -Dbluez_backend=false
# GSM Telephony Support (unnecessary).
CONFIGURE_OPTIONS += -Dofono_backend=false
CONFIGURE_OPTIONS += -Dinspect_tool=false

# don't have required version of libebook
#
# (note that with the exception of the eds backend, the others
# are already excluded above, albeit with a spelling mismatch,
# which is not picked up by meson.)
CONFIGURE_OPTIONS += -Deds_backend=false
CONFIGURE_OPTIONS += -Dofono_backend=false
CONFIGURE_OPTIONS += -Dbluez_backend=false

# reverting to default of tracker being disabled 
# to avoid issues with the gir generation with the updated vala

#LDFLAGS += -z gnu-version-script-compat

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/evolution-data-server
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/libgee
REQUIRED_PACKAGES += library/desktop/search/tracker
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/telepathy-glib
