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
# Copyright (c) 2011, 2024, Oracle and/or its affiliates.
#
BUILD_BITS= 64
COMPILER=gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wget
COMPONENT_VERSION=	1.21.4
COMPONENT_BAID=		158394
COMPONENT_ARCHIVE_HASH= sha256:81542f5cefb8faacc39bbbc6c82ded80e3e4a88505ae72ea51df27525bcde04c
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ANITYA_ID=	5124

PYTHON_VERSION = 3.9

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

include $(WS_MAKE_RULES)/gnu-component.mk

# Keep just the final test report
COMPONENT_TEST_TRANSFORMS += '-ne "/^PASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^FAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^===/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^\# /p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^See/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^Please/p" '

# The tests require 'python3' binary. We create symlink to /usr/bin/python3
# in our test directory
COMPONENT_PRE_TEST_ACTION += rm -f "$(COMPONENT_TEST_BUILD_DIR)/python3";
COMPONENT_PRE_TEST_ACTION += ln -s $(PYTHON) "$(COMPONENT_TEST_BUILD_DIR)/python3";
COMPONENT_TEST_ENV += PATH="$$PATH:$(COMPONENT_TEST_BUILD_DIR)"

# There are two sets of tests. First set fails unless we download some external
# files. That is expected. But without -k argument to gmake the second set is
# not even executed
COMPONENT_TEST_ARGS += -k

# detect OpenSSL 3 headers and libs.
SSL_PKG_CONFIG_PATH.64 = /usr/openssl/3/lib/64/pkgconfig
SSL_PKG_CONFIG_PATH.32 = /usr/openssl/3/lib/pkgconfig
PKG_CONFIG_PATHS += $(SSL_PKG_CONFIG_PATH.$(BITS))

# Enforce openssl (--with-ssl=openssl) instead of default gnutls
# (--with-ssl) as wget doesn't work for secure connections with gnutls. 
# Set PATH to find /usr/perl5/bin/pod2man, so that the man page wget.1
# can be automatically generated
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--without-libpsl
CONFIGURE_OPTIONS +=	--with-ssl=openssl
# openssl3 paths
CONFIGURE_OPTIONS +=	--with-libssl-prefix=/usr/openssl/3
CONFIGURE_ENV.64  +=	OPENSSL_LIBS="-L/usr/openssl/3/lib/64 -lssl -R/lib/$(MACH64)"
CONFIGURE_ENV.64  +=	OPENSSL_CFLAGS="-I/usr/openssl/3/include"

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	PATH="$(PATH):/usr/perl5/bin"
CPPFLAGS +=	-I/usr/include/idn
CONFIGURE_OPTIONS +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	PYTHON=$(PYTHON)

# No proxy settings for the tests because it runs it's own server on localhost
# which can be unreachable via proxy
COMPONENT_TEST_ENV += "http_proxy="
COMPONENT_TEST_ENV += "https_proxy="
COMPONENT_TEST_ENV += "ftp_proxy="
COMPONENT_TEST_ENV += "no_proxy="

REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/security/openssl-3
REQUIRED_PACKAGES += library/zlib
