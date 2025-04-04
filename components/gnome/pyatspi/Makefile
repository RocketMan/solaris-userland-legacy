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

BUILD_BITS =		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyatspi
COMPONENT_VERSION=	2.46.0
COMPONENT_PROJECT_URL=	\
	https://wiki.linuxfoundation.org/accessibility/atk/at-spi/at-spi_on_d-bus
COMPONENT_ARCHIVE_HASH= \
       sha256:d45489cf3d47aa150b1a35e8949b3b31035f8c2075e588d26b6efc625970c62e
COMPONENT_BUGDB=	gnome/a11y-libs-core
COMPONENT_ANITYA_ID=	13157

COMPONENT_BAID=		142448

# replicated from $(WS_MAKE_RULES)/setup.py.mk since this uses configure.mk
CONFIGURE_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.configured)
$(BUILD_DIR)/%-3.7/.configured:		PYTHON_VERSION=3.7
$(BUILD_DIR)/%-3.9/.configured:		PYTHON_VERSION=3.9
$(BUILD_DIR)/%-3.11/.configured:           PYTHON_VERSION=3.11

BUILD_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
$(BUILD_DIR)/%-3.7/.built:		PYTHON_VERSION=3.7
$(BUILD_DIR)/%-3.9/.built:		PYTHON_VERSION=3.9
$(BUILD_DIR)/%-3.11/.built:         PYTHON_VERSION=3.11

INSTALL_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)
$(BUILD_DIR)/%-3.7/.installed:		PYTHON_VERSION=3.7
$(BUILD_DIR)/%-3.9/.installed:		PYTHON_VERSION=3.9
$(BUILD_DIR)/%-3.11/.installed:            PYTHON_VERSION=3.11

TEST_64 = $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared)
$(BUILD_DIR)/%-3.7/.tested-and-compared:		PYTHON_VERSION=3.7
$(BUILD_DIR)/%-3.9/.tested-and-compared:		PYTHON_VERSION=3.9
$(BUILD_DIR)/%-3.11/.tested-and-compared:         PYTHON_VERSION=3.11

# Test transforms retain only relevant results output.
COMPONENT_TEST_TRANSFORMS += \
       '-n ' \
       '-e "/TOTAL: /p" ' \
       '-e "/PASS: /p" ' \
       '-e "/SKIP: /p" ' \
       '-e "/FAIL: /p" ' \
       '-e "/ERROR: /p" ' \

COMPONENT_TEST_MASTER = \
        $(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS).master

include $(WS_MAKE_RULES)/gnome-component.mk
include $(WS_MAKE_RULES)/test-x11.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-tests
CONFIGURE_OPTIONS += --with-python=$(PYTHON)

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES_BASE)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES_BASE)

REQUIRED_PACKAGES += library/python/pygobject-3
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += runtime/python-311

# These are needed to build & run tests, but not for distributed packages
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/python/dbus-python
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
