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
# Copyright (c) 2014, 2024, Oracle and/or its affiliates.
#

COMPILER=gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		PyYAML
COMPONENT_VERSION=	5.4.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c07ab3e6de1e303096b57a3fef386f2e933a242da101608066e8e7a83ff9c0f2
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://pyyaml.org/wiki/PyYAML
COMPONENT_BUGDB=	python-mod/pyyaml
COMPONENT_ANITYA_ID=	4123

COMPONENT_BAID=		95764

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =		$(SOURCE_DIR)
COMPONENT_TEST_ARGS =		tests/lib3/test_all.py

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:	$(SYSTEM_TEST_64)

REQUIRED_PACKAGES += library/libyaml
