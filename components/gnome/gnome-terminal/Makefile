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
# Copyright (c) 2016, 2023, Oracle and/or its affiliates.
#

BUILD_BITS=		64
COMPILER=		clang
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-terminal
COMPONENT_VERSION=	3.50.1
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/Terminal
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	https://gitlab.gnome.org/GNOME/$(COMPONENT_NAME)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:df32b4e5a791e12003ed9179d537767218026eb6d578adb7c481cc830aa98558
COMPONENT_BUGDB=        gnome/terminal
COMPONENT_ANITYA_ID=	10896
BUILD_STYLE=		meson

COMPONENT_BAID=		115294
BUILD_STYLE=		meson

MANIFEST_COMPARE=/usr/bin/true

include $(WS_MAKE_RULES)/gnome-component.mk

ifeq ($(COMPILER),clang)
CXXFLAGS += -D_XPG6 -D_STDC_C99  -stdlib=libc++
CXXFLAGS += -Wno-cast-function-type-strict -Wno-macro-redefined
CFLAGS += -Wno-cast-function-type-strict -Wno-macro-redefined
endif

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# Development files for libuuid (for 11.3)
PKG_CONFIG_PATHS.64 += $(COMPONENT_DIR)/files

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
PKG_CONFIG_PATHS.64 += /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.64 += -L /usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

$(SOLARIS_11_3_ONLY)LDFLAGS += -lssp -lsocket

CONFIGURE_OPTIONS += -Dnautilus_extension=false
CONFIGURE_OPTIONS += -Dsearch_provider=false

unexport SHELLOPTS

REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += gnome/gnome-shell
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libhandy
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/dconf
REQUIRED_PACKAGES += library/gnome/vte3
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/llvm/clang-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
