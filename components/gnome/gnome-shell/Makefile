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
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-shell
COMPONENT_VERSION=	41.9
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/GnomeShell
COMPONENT_ARCHIVE_HASH= \
	sha256:55a3638242e9f5654c5deaed2d7272090df68ec634b3a1dee13ca9110d3c6e23
COMPONENT_BUGDB=        gnome/gnome-shell
COMPONENT_ANITYA_ID=	5409

COMPONENT_BAID=		129244
BUILD_STYLE=            meson

# Workaround the mozjs issue described in 24935318
ifeq ($(MACH), sparc)
ADDITIONAL_PATCHES += patches/08_VM.sparc
COMPONENT_POST_UNPACK_ACTION += $(CP) mapfile.js $(SOURCE_DIR)/src ;
LD_EXEC_OPTIONS.64 += -M $(PWD)/mapfile.js
endif

include $(WS_MAKE_RULES)/gnome-component.mk

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

CXXFLAGS += -std=c++11 -D__EXTENSIONS__

PYTHON_VERSION= 3.11

COMPONENT_POST_UNPACK_ACTION += $(CP) files/* $(SOURCE_DIR)/data/dbus-interfaces ;

# Linux specific
CONFIGURE_OPTIONS += -Dnetworkmanager=false
CONFIGURE_OPTIONS += -Dsystemd=false
# Requires mutter to enable tests - which in turn requires Wayland
CONFIGURE_OPTIONS += -Dtests=false
# Don't build subbprojects
CONFIGURE_OPTIONS += --wrap-mode=nofallback
CONFIGURE_OPTIONS += --libexecdir=$(USRLIB.$(BITS))

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(GNUBIN):$(PATH)

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's?python3?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR)/gnome-shell-extension-tool; \
        $(GSED) -i -e 's?python3?python$(PYTHON_VERSION)?' \
                $(PROTOUSRBINDIR)/gnome-shell-perf-tool;

# evolution-data-server requires nss/nspr, but Solaris doesn't include a 64-bit
# pkg-config file for it, so we workaround this by using the one-off copy in the
# evolution-data-server component directory
PKG_CONFIG_PATHS += $(WS_COMPONENTS)/gnome/evolution-data-server

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += gnome/accessibility/caribou
REQUIRED_PACKAGES += gnome/gnome-clocks
REQUIRED_PACKAGES += gnome/gnome-settings-daemon
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += gnome/window-manager/mutter
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/at-spi2-atk
REQUIRED_PACKAGES += library/desktop/at-spi2-core
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/evolution-data-server
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/geocode-glib
REQUIRED_PACKAGES += library/desktop/gjs
REQUIRED_PACKAGES += library/desktop/gnome-autoar
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/libchamplain
REQUIRED_PACKAGES += library/desktop/libgee
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/folks
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/graphics/cogl
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libical
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/python/pygobject-3-311
REQUIRED_PACKAGES += library/python/simplejson-311
REQUIRED_PACKAGES += library/telepathy-glib
REQUIRED_PACKAGES += runtime/python-311
REQUIRED_PACKAGES += system/display-manager/gdm
REQUIRED_PACKAGES += system/input-method/ibus
REQUIRED_PACKAGES += system/library/accountsservice
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/polkit
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += web/css/sass/sassc
