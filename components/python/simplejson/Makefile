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
# Copyright (c) 2013, 2023, Oracle and/or its affiliates.
#

include ../../../make-rules/shared-macros.mk
COMPILER=	gcc

COMPONENT_NAME=		simplejson
COMPONENT_VERSION=	3.18.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:6197cfebe659ac802a686b5408494115a7062b45cdf37679c4d6a9d4f39649b7
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/simplejson/simplejson
COMPONENT_BUGDB=	python-mod/simplejson
COMPONENT_ANITYA_ID=	4026
COMPONENT_BAID=		141687

MANIFEST_COMPARE=/usr/bin/true

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ifeq ($(OS_VERSION),11.3)
OLD_DESKTOP_BUILD=	0.5.11,5.11-0.175.2.0.0.20.0
else
OLD_DESKTOP_BUILD=	5.12-5.12.0.0.0.14.0
endif

PKG_MACROS +=		OLD_DESKTOP_BUILD=$(OLD_DESKTOP_BUILD)

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/$(COMPONENT_NAME)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TEST_32_and_64)

REQUIRED_PACKAGES += system/library
