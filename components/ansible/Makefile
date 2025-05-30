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
# Copyright (c) 2021, 2023, Oracle and/or its affiliates.
#

BUILD_BITS= NO_ARCH
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ansible
COMPONENT_VERSION=	2.14.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a7bf492c224080eefffd609338fb71f73f67a03f8a0471dfcd05894b5b6aebd4
COMPONENT_ARCHIVE_URL=	\
    https://github.com/ansible/ansible/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://github.com/ansible/ansible
COMPONENT_BUGDB=	utility/ansible
COMPONENT_ANITYA_ID=	13227

COMPONENT_BAID=		136325
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

# We need just a single version
PYTHON_VERSIONS=	3.11

# Tests requires ddt which is not integrated
TEST_TARGET= $(NO_TESTS)

BUILD_STYLE= setup.py

ASLR_MODE= $(ASLR_NOT_APPLICABLE)

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)
PKG_MACROS +=		PYV=$(shell echo $(PYTHON_VERSIONS) | tr -d .)

# Copy the PKG-INFO file to the build root
COMPONENT_PRE_BUILD_ACTION = \
    $(CP) $(COMPONENT_DIR)/PKG-INFO $(SOURCE_DIR)

# Copy the man page to the standard man page location
ANSIBLE_MAN = ansible.1
COMPONENT_POST_INSTALL_ACTION += \
    cd $(COMPONENT_DIR) ; \
    $(MKDIR) $(PROTOUSRSHAREMAN1DIR) ; \
    $(INSTALL) --mode=644 $(COMPONENT_DIR)/files/man1/$(ANSIBLE_MAN) \
      $(PROTOUSRSHAREMAN1DIR)/

REQUIRED_PACKAGES += $(PYVS:%=runtime/python-%)
REQUIRED_PACKAGES += $(PYVS:%=library/python/cryptography-%)
REQUIRED_PACKAGES += $(PYVS:%=library/python/jinja2-%)
REQUIRED_PACKAGES += $(PYVS:%=library/python/packaging-%)
REQUIRED_PACKAGES += $(PYVS:%=library/python/pyyaml-%)
REQUIRED_PACKAGES += $(PYVS:%=library/python/importlib-metadata-%)
REQUIRED_PACKAGES += library/python/resolvelib
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
