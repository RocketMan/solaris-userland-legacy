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

BUILD_BITS=		64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
# Also, for now, all things built for C++11 require gcc.
COMPILER=gcc

# The Makefile of this component does not support multiple build jobs.
COMPONENT_MAKE_JOBS=1

include ../../../make-rules/shared-macros.mk

# Despite its name, evolution-data-server is no longer just a backend for the
# Evolution Mail Client; it is also a backend for various bits of data that
# GNOME stores and various components now expect it to be present.

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_NAME=		evolution-data-server
COMPONENT_VERSION=	3.42.5
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/Evolution
COMPONENT_ARCHIVE_HASH= \
	sha256:a23ee8ebdbf2efddaac05b291fec6d203ad2fce359f911607b682cdb0bc23f53
COMPONENT_BUGDB=        gnome/libraries
COMPONENT_ANITYA_ID=	10935

COMPONENT_BAID=		123941

BUILD_STYLE= cmake

include $(WS_MAKE_RULES)/gnome-component.mk

# __EXTENSIONS__ required for timezone, altzone variables.
CFLAGS += -D__EXTENSIONS__ -DHAVE_SUN_KRB5
CXXFLAGS += -std=c++11 -D__EXTENSIONS__ -DHAVE_SUN_KRB5
CPPFLAGS += -I/usr/include/kerberosv5/
CFLAGS += $(XPG6MODE)

LDFLAGS.32 += -L/usr/lib
LDFLAGS += $(LDFLAGS.$(BITS)) -lm -lsocket -lnsl -licui18n_gcc -licuuc_gcc

CMAKE_OPTIONS += -DENABLE_GOOGLE_AUTH=OFF
CMAKE_OPTIONS += -DENABLE_OAUTH2=OFF
CMAKE_OPTIONS += -DENABLE_UOA=OFF
CMAKE_OPTIONS += -DENABLE_INTROSPECTION=ON
CMAKE_OPTIONS += -DENABLE_GTK_DOC=OFF
CMAKE_OPTIONS += -DOPEN_LDAP=OFF
CMAKE_OPTIONS += -DENABLE_VALA_BINDINGS=ON
CMAKE_OPTIONS += -DWITH_KRB5=OFF
CMAKE_OPTIONS += -DWITH_OPENLDAP=OFF
CMAKE_OPTIONS += -DENABLE_IPV6=OFF
CMAKE_OPTIONS += -DENABLE_WEATHER=OFF
CMAKE_OPTIONS += -DENABLE_GOOGLE=OFF
CMAKE_OPTIONS += -DSYSCONF_INSTALL_DIR="/etc"
CMAKE_OPTIONS.32 += -DENABLE_GOA=OFF
CMAKE_OPTIONS.32 += -DENABLE_GTK=OFF
CMAKE_OPTIONS.32 += -DCC_BITS=$(CC_BITS)

#CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON

# g-ir-scanner
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)


# for the tests
unexport SHELLOPTS

include $(WS_MAKE_RULES)/test-x11.mk

#
# to locate dbus-daemon
# NOTE: desktop must be running -> run
# vncserver
# and export DISPLAY
#
COMPONENT_TEST_ENV += PATH="$(PATH):/usr/lib"
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMER =    $(NAWK)
COMPONENT_TEST_TRANSFORMS = -F"'('" \
	"'/The following tests FAILED/ {results = 1}; /Errors while running CTest/ {results = 0}; {if (results) print \$$1}'"

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk4
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/icu-gcc
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libical
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/security/nss
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += security/kerberos-5/kdc
REQUIRED_PACKAGES += system/library/iconv
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/network/ldap/openldap

