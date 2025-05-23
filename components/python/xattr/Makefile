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
# Copyright (c) 2014, 2023, Oracle and/or its affiliates.
#

# Component uses ABI3 naming.
PYTHON3_SOABI=abi3
COMPILER=gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xattr
COMPONENT_VERSION=	0.10.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c12e7d81ffaa0605b3ac8c22c2994a8e18a9cf1c59287a1b7722a2289c952ec5
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/xattr/xattr
COMPONENT_BUGDB=	python-mod/xattr
COMPONENT_ANITYA_ID=	21273
COMPONENT_BAID=		141690

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/pybuild.mk
include $(WS_MAKE_RULES)/ips.mk

# The test suite wants to use some unicode filenames, which don't work in the C
# locale.
COMPONENT_TEST_ENV +=	LC_ALL=en_US.UTF-8
COMPONENT_TEST_DIR =	$(@D)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

COMPONENT_POST_INSTALL_ACTION += \
    (cd $(PROTO_DIR)/usr/bin; $(MV) xattr xattr-$(PYTHON_VERSION))

# Tests run under setuptools work very hard to run in the source directory
# itself, and will thus blow up with an VerificationError (wrong ELF class)
# when running 64-bit tests after 32-bit or vice-versa.  So copy the source off
# to a target-specific directory and run the tests.  Note that this will also
# rebuild the package, since it doesn't want to use what it should already be
# finding in PYTHONPATH.
COMPONENT_PRE_TEST_ACTION = $(CP) -r $(SOURCE_DIR) $(@D)/tests

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:	$(SYSTEM_TEST_32_and_64)

REQUIRED_PACKAGES += $(PYVS:%=library/python/cffi-%)
REQUIRED_PACKAGES += system/library
