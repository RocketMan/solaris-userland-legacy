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
# Copyright (c) 2016, 2022, Oracle and/or its affiliates.
#

# Parallel build jobs are supported only if GNU make is used.
COMPONENT_MAKE_JOBS=1
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		serf
COMPONENT_VERSION=	1.3.9
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://serf.apache.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:549c2d21c577a8a9c0450facb5cca809f26591f048e466552240947bdf7a87cc
COMPONENT_ARCHIVE_URL=	https://www.apache.org/dist/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
#COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	library/libserf
COMPONENT_ANITYA_ID=	1720

COMPONENT_BAID=		38440

include $(WS_MAKE_RULES)/prep.mk
# Needed by the test: target. We override build and install.
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

USED_APR =		/usr/apr/1.5
USED_APU =		/usr/apr-util/1.5

APR_32 =		$(USED_APR)/bin/apr-1-config
APR_64 =		$(USED_APR)/bin/$(MACH64)/apr-1-config
APU_32 =		$(USED_APU)/bin/apu-1-config
APU_64 =		$(USED_APU)/bin/$(MACH64)/apu-1-config
SERFLIBPATH_32 =	-R$(USED_APR)/lib -R$(USED_APU)/lib
SERFLIBPATH_64 =	-R$(USED_APR)/lib/64 -R$(USED_APU)/lib/64
SERFLIBDIR_32 =		/usr/lib
SERFLIBDIR_64 =		/usr/lib/64
ifneq ($(strip $(OPENSSL3)),)
OPENSSL_LIBDIR_32 =	/usr/openssl/3/lib
OPENSSL_LIBDIR_64 =	/usr/openssl/3/lib/$(MACH64)
endif

# We have to roll our own as serf is built with scons.
SCONS =			/usr/bin/scons
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS +=	CPPFLAGS=-D__EXTENSIONS__
COMPONENT_BUILD_ARGS +=	CFLAGS="$(CC_BITS) -KPIC"
COMPONENT_BUILD_ARGS +=	LINKFLAGS="$(CC_BITS) $(SERFLIBPATH_$(BITS))"
COMPONENT_BUILD_ARGS += APR=$(APR_$(BITS))
COMPONENT_BUILD_ARGS += APU=$(APU_$(BITS))
COMPONENT_BUILD_ARGS += PREFIX=/usr
COMPONENT_BUILD_ARGS += LIBDIR=$(SERFLIBDIR_$(BITS))
ifneq ($(strip $(OPENSSL3)),)
COMPONENT_BUILD_ARGS += OPENSSL=/usr/openssl/3
COMPONENT_BUILD_ARGS += OPENSSL_LIBDIR=$(OPENSSL_LIBDIR_$(BITS))
endif

COMPONENT_TEST_CMD =	$(SCONS)
ifneq ($(strip $(OPENSSL3)),)
# Serf test test_ssl_handshake doesn't work correctly with OpenSSL 3.
# There is ongoing upstream work to fix those tests:
# https://github.com/apache/serf/commit/65b17ccf8badbe3911e8a71e6a735f7ea0dcef32
# https://github.com/apache/serf/commit/70c9d83f7e013199b53b2c2fd11dcb2d90749c69
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master.openssl3
else
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master
endif

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^cc /d" ' \
	'-e "/warning:/d"' \
	'-e "/prototype:/d"' \
	'-e "/developerstudio/d"' \
	'-e "/\.\.\.\.\.\.\.\.\./d"' \
	'-e "/argument/d"'

$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	(cd $(@D) ; $(SCONS) $(COMPONENT_BUILD_ARGS))
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(@D)
endif
	$(TOUCH) $@

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

# As there aren't many files, just get them out of the build directory.
install:	build

test:		$(TEST_32_and_64)

system-test:	$(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += developer/build/scons-27
REQUIRED_PACKAGES += library/apr-15
REQUIRED_PACKAGES += library/apr-util-15
REQUIRED_PACKAGES += developer/build/scons
REQUIRED_PACKAGES += library/apr-1
REQUIRED_PACKAGES += library/apr-util-1
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/openldap
ifneq ($(strip $(OPENSSL3)),)
REQUIRED_PACKAGES += library/security/openssl-3
else
REQUIRED_PACKAGES += library/security/openssl
endif
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network/ldap/openldap
