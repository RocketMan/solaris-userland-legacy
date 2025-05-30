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

BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsndfile
COMPONENT_VERSION=	1.1.0
COMPONENT_PROJECT_URL=	http://libsndfile.github.io/libsndfile/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0f98e101c0f7c850a71225fb5feaf33b106227b3d331333ddc9bacee190bcf41
COMPONENT_ARCHIVE_URL=	\
	https://github.com/libsndfile/libsndfile/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
#COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	library/libsndfile
COMPONENT_ANITYA_ID=	13277
COMPONENT_BAID=		127281

PYTHON_VERSION = 3.11

TEST_TARGET= install $(TEST_32_and_64)
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_32_and_64)

include $(WS_MAKE_RULES)/common.mk

# Use explicit Python version rather than the default one
CONFIGURE_ENV += PYTHON=$(PYTHON)

# Needed to get tests/header_test.c to compile successfully on SPARC.
gcc_XREGS.sparc=	-mapp-regs

# Get correct libsndfile.so.1 from the proto area.
TEST_LIBPATH.32 =	$(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =	$(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

# Need to use GNU sed otherwise we get a:
# Error : sfversion <version> and PACKAGE_VERSION <version> don't match."
# failure from the test_wrapper.sh script.
COMPONENT_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"
COMPONENT_SYSTEM_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"

COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|libsndfile-1\.0\...|libsndfile-1\.0\.xx|g" ' \
	'-e "/FILE_OFFSET_BITS/d"' \
	'-n ' \
	'-e "/-------/p" ' \
	'-e "/=======/p" ' \
	'-e "/ passed /p" ' \
	'-e "/ failed /p" ' \
	'-e "/^Testing/p" ' \
	'-e "/dev\/full/p" ' \
	'-e "/^\./p" ' \
	'-e "/ok$$/p" '

REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/libogg
REQUIRED_PACKAGES += codec/libvorbis
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library/math
