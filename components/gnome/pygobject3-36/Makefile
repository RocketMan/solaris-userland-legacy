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
# Copyright (c) 2016, 2020, Oracle and/or its affiliates.
#

# gobject-introspection bindings are only built correctly for gtk when building
# with gcc, this would otherwise build with Studio.
COMPILER =		gcc
BUILD_BITS =		64
BUILD_STYLE =		meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pygobject
COMPONENT_VERSION=	3.36.1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/PyGObject
COMPONENT_ARCHIVE_HASH= \
	sha256:d1bf42802d1cec113b5adaa0e7bf7f3745b44521dc2163588d276d5cd61d718f
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	13158

TPNO=			35809

PKG_CONFIG_PATHS+=$(PYTHON_VENDOR_PACKAGES_BASE)/lib/pkgconfig/

PYTHON_VERSIONS=        $(PYTHON3_VERSIONS)

# replicated from $(WS_MAKE_RULES)/setup.py.mk since this uses configure.mk
CONFIGURE_64 += $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.configured)
$(BUILD_DIR)/%-3.5/.configured:		PYTHON_VERSION=3.5
$(BUILD_DIR)/%-3.5/.configured:		PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES_BASE)
$(BUILD_DIR)/%-3.7/.configured:		PYTHON_VERSION=3.7
$(BUILD_DIR)/%-3.7/.configured:		PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES_BASE)
$(BUILD_DIR)/$(MACH64)-%/.configured:	BITS=64

BUILD_64 += $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
$(BUILD_DIR)/%-3.5/.built:		PYTHON_VERSION=3.5
$(BUILD_DIR)/%-3.7/.built:		PYTHON_VERSION=3.7
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64

INSTALL_64 += $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)
$(BUILD_DIR)/%-3.5/.installed:		PYTHON_VERSION=3.5
$(BUILD_DIR)/%-3.7/.installed:		PYTHON_VERSION=3.7
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64

# Tests do not yet work with Userland framework - 23712631
TEST_TARGET= $(SKIP_TEST)
include $(WS_MAKE_RULES)/gnome-component.mk

# Required due to patch to configure.ac.
# The TERM is required because autogen.sh calls /usr/bin/gnome-autogen.sh which
# in turn calls `tput bold` which may fail if you have TERM unknown to the
# current build machine.
#COMPONENT_PREP_ACTION += ( cd $(@D) ; TERM=vt100 NOCONFIGURE=1 $(CONFIG_SHELL) autogen.sh );

# Needs -std=c99 at minimum for 'NAN', etc.
CFLAGS += -std=c11
CFLAGS += -I$(PYTHON_VENDOR_PACKAGES)/cairo/include

CONFIGURE_OPTIONS += -Ddefault_library=shared

# The build process modifies the shebang line to use the version of Python
# automatically found; to avoid using the current system default, one is
# explicitly specified here.
CONFIGURE_OPTIONS += -Dpython=$(PYTHON)

CONFIGURE_OPTIONS += -Dlibpython-dir=$(PYTHON_VENDOR_PACKAGES)

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

# Override $(PYTHON) for configure step so that configure can find
# $(PYTHON)-config properly
$(BUILD_DIR)/%-3.5/.configured:	PYTHON=$(PYTHON.3.5)m
$(BUILD_DIR)/%-3.7/.configured:	PYTHON=$(PYTHON.3.7)m

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/python/pycairo
# Pyflakes is needed for tests, but not build or install
REQUIRED_PACKAGES += library/python/pyflakes
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
