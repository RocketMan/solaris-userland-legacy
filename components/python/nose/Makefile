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

COMPONENT_NAME=		nose
COMPONENT_VERSION=	1.3.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/nose-devs/nose
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f1bffef9cbc82628f6e7d7b40d7e255aefaa1adb6a1b1d26c69a8b79e6208a98
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/n/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	python-mod/nose
COMPONENT_ANITYA_ID=	3938
COMPONENT_BAID=		34611

# Nose isn't (and won't be) compatible with Python 3.11
PYTHON_VERSIONS = $(WITHOUT_PYTHON3.11)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# nose ships the tests in Python 2 syntax, and uses setup.py build_tests
# to convert them to Python 3 syntax, but doing so requires running Python 3.
$(SOURCE_DIR)/.prep:	PYTHON_VERSION=3.7

COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_ARGS =	selftest.py

# Used to automatically run the Python 2.6 nose tests even though there was
# an error found when running one of the Python 2.7 ones.
COMPONENT_TEST_ARGS +=	|| true

# Save an original copy of the test script to be able to edit it correctly
# for each version of Python and build the tests once.
COMPONENT_PREP_ACTION += \
	($(CP) $(SOURCE_DIR)/selftest.py $(SOURCE_DIR)/selftest.py.orig ; \
	cd $(COMPONENT_TEST_DIR); $(COMPONENT_TEST_ENV_CMD) \
                $(COMPONENT_TEST_ENV) \
                $(COMPONENT_TEST_CMD) setup.py build_tests)

# We need to adjust the script that is used to run the tests, to pick the
# appropriate nose in the proto area depending upon which version of Python
# we are running the tests against.
COMPONENT_PRE_TEST_ACTION = \
	$(GSED) -e "s|'build', 'lib\*'|'..', 'build', 'prototype', '$(MACH)', 'usr', 'lib', 'python$(PYTHON_VERSION)', 'vendor-packages\*'|" \
		$(SOURCE_DIR)/selftest.py.orig > $(SOURCE_DIR)/selftest.py

# Make all files Python 3 compatible
COMPONENT_POST_BUILD_ACTION += \
	2to3-$(PYTHON_VERSION) -nw --no-diffs $(@D)/lib/nose;

# The test output can contain non-deterministic results because "chances are
# you will experience odd, intermittent and unexplainable failures and errors"
# when using the multiprocess plug. See:
# http://nose.readthedocs.org/en/latest/plugins/multiprocess.html
# CR #20470423 has been filed to investigate these failures.
#
# Because of this we use nawk to just extract lines starting with:
# ERROR: ...
# Ran 3XX tests in ...
# FAILED ...
# OK
# stripping out the random portions (like time to complete the tests).
COMPONENT_TEST_TRANSFORMER =	$(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/^ERROR: / { print }; /^Ran / { sub(\" test.+in .+s\", \" tests in\"); print }; /^FAILED / { print }; /^OK / { print };'"

COMPONENT_SYSTEM_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_SYSTEM_TEST_ENV =
COMPONENT_SYSTEM_TEST_ARGS =	selftest.py

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TEST_NO_ARCH)
