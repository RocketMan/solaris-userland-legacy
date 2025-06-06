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
# Copyright (c) 2020, 2023, Oracle and/or its affiliates.
#
BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =	libzip
COMPONENT_VERSION =	1.9.2
COMPONENT_PROJECT_URL =	https://libzip.org/
COMPONENT_ARCHIVE_HASH = \
    sha256:d98d9dd49c2580314923c262a28c3f8a3e77e1b612da00b7fe220851ccd465ce
COMPONENT_ARCHIVE_URL = $(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/zip
COMPONENT_ANITYA_ID=	10649
COMPONENT_BAID =	126980

BUILD_STYLE= cmake

include $(WS_MAKE_RULES)/common.mk

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
PKG_CONFIG_PATHS.32 += /usr/lib/pkgconfig/gnutls-3
PKG_CONFIG_PATHS.64 += /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L /usr/lib/gnutls-3
LD_OPTIONS.64 += -L /usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

# elfedit removes wrong RUNPATH/RPATH 
COMPONENT_POST_INSTALL_ACTION.64 = ( \
	for i in bin/zipcmp bin/zipmerge bin/ziptool \
	         lib/libzip.so.5.5 lib/$(MACH64)/libzip.so.5.5; do \
 	$(ELFEDIT) -e "dyn:delete RUNPATH" -e "dyn:delete RPATH" \
 	  $(PROTOUSRDIR)/$$i ; done ) ;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += '-e "s/  *[0-9][0-9]*\.[0-9][0-9] sec//" ' 
COMPONENT_TEST_TRANSFORMS += '-e "/^make/d" -e "/^Built/d" -e "/^Scanning dependencies/d" '

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/security/nettle
REQUIRED_PACKAGES += library/zlib
