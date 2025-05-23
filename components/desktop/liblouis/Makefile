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
# Copyright (c) 2016, 2024, Oracle and/or its affiliates.
#

BUILD_BITS= 		64
COMPILER=		gcc

# The Makefile of this component does not support multiple build jobs.
COMPONENT_MAKE_JOBS=1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		liblouis
COMPONENT_VERSION=	3.25.0
COMPONENT_PROJECT_URL=	http://liblouis.org/
COMPONENT_ARCHIVE_HASH= \
	sha256:d720aa5fcd51de925a28ae801b8b2ca76ee67e2360b40055c679bce8e565f251
COMPONENT_ARCHIVE_URL=	https://github.com/liblouis/liblouis/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/accessibility
COMPONENT_ANITYA_ID=	13112
COMPONENT_BAID=		141830

# Orca uses python 3.11, so we need to match
PYTHON_VERSION=		3.11
PKG_MACROS+=		PYVER="$(PYTHON_VERSION)"

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=    --enable-shared
CONFIGURE_OPTIONS +=    --disable-static
CONFIGURE_OPTIONS +=    --enable-ucs4

# While the main library is built with configure, the python module is
# built & installed with separate invocations of setup.py
PYTHON_ENV +=	CC="$(CC)"
PYTHON_ENV +=	CFLAGS="$(CFLAGS)"
PYTHON_ENV +=	PYTHONPATH='$(@D)/python'

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D)) ;
COMPONENT_POST_BUILD_ACTION += \
	(cd $(@D)/python ; \
	    $(ENV) $(COMPONENT_BUILD_ENV) $(PYTHON_ENV) \
		LD_LIBRARY_PATH_$(BITS)=$(@D)/liblouis/.libs/ \
	        $(PYTHON) ./setup.py build );
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(@D)/python ; \
	    $(ENV) $(COMPONENT_INSTALL_ENV) $(PYTHON_ENV) \
		LD_LIBRARY_PATH_$(BITS)=$(PROTO_DIR)$(USRLIB.$(BITS)) \
	        $(PYTHON) ./setup.py install --root $(PROTO_DIR) \
		--install-lib $(PYTHON_LIB) );

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

# Standard automake test framework results transform
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL/p" ' \
        '-e "/SKIP/p" ' \
        '-e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/ERROR/p" '

# additional transforms for brltty
COMPONENT_TEST_TRANSFORMS += \
        '-e "/^==*$$/p" ' \
        '-e "/expected/p" '

REQUIRED_PACKAGES += developer/documentation-tool/help2man
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-311
REQUIRED_PACKAGES += system/core-os
