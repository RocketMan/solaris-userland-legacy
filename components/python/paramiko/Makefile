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
# Copyright (c) 2012, 2023, Oracle and/or its affiliates.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		paramiko
COMPONENT_VERSION=	2.11.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:62963cb5ca607456bac881e8e293255397bd84d54f02fff13aa8b82bdcef6412
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/paramiko/paramiko/
COMPONENT_BUGDB=	python-mod/paramiko
COMPONENT_ANITYA_ID=	3954
COMPONENT_BAID=		127757

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# set LC_ALL for unicode sftp tests test_K_utf8 and test_L_utf8_chdir
COMPONENT_TEST_ENV =	LC_ALL=en_US.UTF-8
COMPONENT_TEST_ENV +=	PYTHONPATH=$(SOURCE_DIR)
COMPONENT_SYSTEM_TEST_ENV =	LC_ALL=en_US.UTF-8

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:	$(SYSTEM_TEST_NO_ARCH)

REQUIRED_PACKAGES += $(PYVS:%=library/python/bcrypt-%)
REQUIRED_PACKAGES += $(PYVS:%=library/python/cryptography-%)
REQUIRED_PACKAGES += $(PYVS:%=library/python/six-%)
# locale required for unicode sftp tests
REQUIRED_PACKAGES += system/locale
