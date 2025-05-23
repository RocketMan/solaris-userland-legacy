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
# Copyright (c) 2015, 2022, Oracle and/or its affiliates.
#

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              clang
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vte
COMPONENT_VERSION=	0.74.2
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/Terminal/VTE
COMPONENT_ARCHIVE_HASH= \
	sha256:a535fb2a98fea8a2449cd1a02cccf5190131dddff52e715afdace3feb536eae7
COMPONENT_BUGDB=        gnome/terminal
COMPONENT_ANITYA_ID=	10895

COMPONENT_BAID=		110816
BUILD_STYLE=		meson

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/gnome-component.mk

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

ifeq ($(COMPILER),clang)
CXXFLAGS += -stdlib=libc++
CXXFLAGS += -Wno-cast-function-type-strict -Wno-macro-redefined
CFLAGS += -Wno-cast-function-type-strict -Wno-macro-redefined
endif

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(GNUBIN):$(PATH)

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
PKG_CONFIG_PATHS.32 += /usr/lib/pkgconfig/gnutls-3
PKG_CONFIG_PATHS.64 += /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L /usr/lib/gnutls-3
LD_OPTIONS.64 += -L /usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))
LDFLAGS += -lssp

# if you are on 11.3 and are using stock gcc which does NOT have the
# 910-legacy-xpg4 patch from this repo, then uncomment the following
# line to work-around strict XPG4 semantics.
#$(SOLARIS_11_3_ONLY)CXXFLAGS += -DSTRICT_XPG4

CONFIGURE_OPTIONS += -D_b_symbolic_functions=false
CONFIGURE_OPTIONS += -D_systemd=false
#CONFIGURE_OPTIONS += -Ddebugg=true
#CONFIGURE_OPTIONS += --buildtype debug

CONFIGURE_OPTIONS.32 += -Dgtk4=false
CONFIGURE_OPTIONS.32 += -Dgir=false
CONFIGURE_OPTIONS.32 += -Dvapi=false

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/fribidi
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/llvm/clang-c++-runtime
REQUIRED_PACKAGES += system/library/math
