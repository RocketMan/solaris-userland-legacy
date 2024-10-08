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
# Copyright (c) 2011, 2023, Oracle and/or its affiliates.
#

COMPILER=	gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME_BASE=	lxml
$(SOLARIS_11_3_ONLY)COMPONENT_NAME=$(COMPONENT_NAME_BASE)3
$(SOLARIS_11_4_5_ONLY)COMPONENT_NAME=$(COMPONENT_NAME_BASE)
COMPONENT_VERSION=	4.9.1
COMPONENT_PROJECT_URL=	http://lxml.de/
COMPONENT_SRC=		$(COMPONENT_NAME_BASE)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fe749b052bb7233fe5d072fcb549221a8cb1a16725c47c37e42b0b9cb3ff2c3f
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/lxml
COMPONENT_ANITYA_ID=	48378
COMPONENT_BAID=		128302

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk

# for 11.3, we want python3 only, as beadm depends on the legacy lxml-27.
$(SOLARIS_11_3_ONLY)PYTHON2_VERSIONS=
$(SOLARIS_11_3_ONLY)PYTHON_VERSIONS= $(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_ARGS=	test
COMPONENT_TEST_CMD=	$(MAKE) -i
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)

# Prevent errors like: 'UnicodeEncodeError: 'ascii' codec can't encode
# characters in position 5-18: ordinal not in range(128)'
# Taken from https://illumos.org/issues/6538
COMPONENT_TEST_ENV+=	LC_ALL=en_US.UTF-8

# Point the test suite to already built libraries and
# stop it from rebuilding everything during testing.
COMPONENT_TEST_ENV+=	HOME=$(BUILD_DIR)/config-$*

# Prevent errors like: OSError: Error reading file 'http://127.0.0.1:59951/':
# failed to load HTTP resource
COMPONENT_TEST_ENV+=	http_proxy=
COMPONENT_TEST_ENV+=	https_proxy=
COMPONENT_TEST_ENV+=	HTTP_PROXY=
COMPONENT_TEST_ENV+=	HTTPS_PROXY=

# Use the correct version of Python each time.
COMPONENT_TEST_ENV+=	PYTHON=$(PYTHON)

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/OK/p" ' \
	'-e "/FAILED/p" ' \
	'-e "s|\(Ran [0-9][0-9]* tests\).*|\1|p" '

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
