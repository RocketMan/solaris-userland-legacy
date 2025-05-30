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
# Copyright (c) 2015, 2022, Oracle and/or its affiliates.
#
BUILD_BITS= 64
# Must use gcc because of 21090206
COMPILER= gcc

include ../../../make-rules/shared-macros.mk

MAJOR_VERSION=7.4
MICRO_VERSION=33

COMPONENT_NAME=		php
COMPONENT_VERSION=	$(MAJOR_VERSION).$(MICRO_VERSION)
UL_PHP_MINOR_VERSION=	$(MAJOR_VERSION)
COMPONENT_PROJECT_URL=	http://php.net/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=\
    sha256:924846abf93bc613815c55dd3f5809377813ac62a9ec4eb3778675b82a27b927
COMPONENT_ARCHIVE_URL=	http://php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror
COMPONENT_ANITYA_ID=	57896

COMPONENT_BAID=		132751
COMPONENT_BAID_IMAP=	37002

include $(WS_MAKE_RULES)/common.mk
include $(PHP_TOP_DIR)/php.mk

PKG_MACROS+= MAJOR_VERSION=$(MAJOR_VERSION)
PKG_MACROS+= EXTENSIONS=no-debug-zts-20190902

# NOTES: See http://php.net/manual/en/install.unix.apache2.php
# The contents of files/php7.3.conf would normally go into Apache's httpd.conf
# but we put it in a separate file for our convenience.
# See http://php.net/manual/en/configuration.file.php
# The contents of files/extensions.ini would normally go into php.ini file

# but is in a separate file for our convenience.
# Both of these files are hand crafted.

# need GCC_ROOT/bin for configure, usr/sbin for dtrace 
export PATH=$(GCC_ROOT)/bin:$(GNUBIN):$(USRBINDIR):$(USRSBINDIR)

# We patch configure.in to allow building just modules (no SAPI's), e.g. intl.
# Since we are sharing the source, regenerate configure here.
COMPONENT_PREP_ACTION += (cd $(SOURCE_DIR) ; autoreconf) ;

include enable-extensions.mk

CONFIGURE_OPTIONS += --enable-dtrace
CONFIGURE_OPTIONS += --enable-maintainer-zts

# Without this, the build seems to interrogate GCC for potential library
# search path information and then embed it into the RUNPATH of selected ELF
# files it creates.  This includes GCC private directories
CONFIGURE_OPTIONS += --disable-rpath

ETCPHPDIR= $(ETCDIR)/php/$(MAJOR_VERSION)
VARPHPDIR= $(VARDIR)/php/$(MAJOR_VERSION)
CONFIGURE_OPTIONS +=	--with-libdir=lib/$(MACH64)
# .conf files go under /etc, not /usr
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCPHPDIR)
# var doesn't go under /usr either!
CONFIGURE_OPTIONS +=	--localstatedir=$(VARPHPDIR)
# Nor does php.ini and its friends.
CONFIGURE_OPTIONS +=	--with-config-file-path=$(ETCPHPDIR)
CONFIGURE_OPTIONS +=	--with-config-file-scan-dir=$(ETCPHPDIR)/conf.d
# Nor does PEAR (default: $PREFIX/lib/php)
CONFIGURE_OPTIONS +=	--with-pear=$(VARPHPDIR)/pear
# No debug php's.  They won't build anyways.
CONFIGURE_OPTIONS +=	--disable-phpdbg
CONFIGURE_OPTIONS +=	--disable-phpdbg-webhelper
CONFIGURE_OPTIONS +=	--disable-phpdbg-debug
# if debug is desired do this
# https://bugs.php.net/bugs-generating-backtrace.php
# CONFIGURE_OPTIONS +=    --enable-debug

# JM 2020-03-28 disable kerberos support
CONFIGURE_OPTIONS +=   --without-kerberos

# icu's switch to g++
# 21090206 icu should build C++ to C++11
# causes this in php forcing php to switch also
# 23003672 PHP fails all or most tests
CXXFLAGS += -std=c++11
CONFIGURE_OPTIONS += CXXFLAGS="$(CXXFLAGS)"

# Use openldap
# This is good enough to fool configure
CPPFLAGS += -I$(USRINCDIR)/openldap
LDFLAGS += -lldap_r
# but ensure "make" gets the point
COMPONENT_BUILD_ARGS += LDAP_SHARED_LIBADD="-lldap_r"

CFLAGS += -std=gnu99

# JM 2020-03-28 for 11.3
CFLAGS += -D__EXTENSIONS__ -D_XOPEN_SOURCE=600 -D_XPG6

# Disable SSLv2 and SSLv3 for security reasons
CFLAGS += -DOPENSSL_NO_SSL2
CFLAGS += -DOPENSSL_NO_SSL3

PROTOUSRPHPVERDIR = $(PROTO_DIR)/$(CONFIGURE_PREFIX)

COMPONENT_PRE_CONFIGURE_ACTION += $(MKDIR) $(BUILD_DIR)/temp;
COMPONENT_BUILD_ENV += TMPDIR=$(BUILD_DIR)/temp
CONFIGURE_ENV += TMPDIR=$(BUILD_DIR)/temp
COMPONENT_INSTALL_ENV += TMPDIR=$(BUILD_DIR)/temp

# In order to build pear on public build machine every engineer needs to use
# his own temporary directory and not /var/tmp/pear. Unfortunately this
# temporary directory is then stored into pear.conf file. So we need to correct
# it back to the default which would be used without us specifying TMPDIR -
# that is to /tmp/pear/temp
COMPONENT_POST_INSTALL_ACTION += \
	../fix_temp_dirs.pl \
	    $(PROTO_DIR)/etc/php/$(MAJOR_VERSION)/pear.conf \
	    $(BUILD_DIR)/temp ;

# Adapted from PHP 5.3 Makefile.
# Creates alternate versions of the scripts needed for building extensions
# separately, since the generated versions of these scripts hardcode
# configuration for a PHP that is installed on the system.
COMPONENT_POST_INSTALL_ACTION += \
	( set -e; \
	mkdir -p proto-scripts; \
	cat $(BUILD_DIR_64)/scripts/phpize | \
	 sed -e "s,^\#!/bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(PROTOUSRPHPVERDIR)%" | \
	 sed -e "s%^includedir=.*%includedir=$(PROTOUSRPHPVERDIR)/include/php%" | \
	 sed -e "s%^phpdir=.*%phpdir=$(SOURCE_DIR)%"  | \
	 sed -e "s%phpdir/phpize.m4%phpdir/scripts/phpize.m4%" | \
	 sed -e "s%$PHP_AUTOCONF   || exit 1%$PHP_AUTOCONF -f   || exit 1%" | \
	 sed -e "s%$PHP_AUTOHEADER || exit 1%$PHP_AUTOHEADER -f || exit 1%" | \
	 sed -e 's%(cd "$$phpdir" && cp $$FILES_BUILD "$$builddir"/build)%(cd "$$phpdir/build" \&\& cp $$FILES_BUILD "$$builddir"/build)%' | \
	 sed -e "s%^builddir=.*%builddir=$(BUILD_DIR_64)%" \
	 > proto-scripts/phpize-proto ; \
	chmod 755 proto-scripts/phpize-proto ) ; \
	( set -e; \
	 cat $(BUILD_DIR_64)/scripts/php-config | \
	 sed -e "s,^\#! /bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(PROTOUSRPHPVERDIR)%" | \
	 sed -e "s%^include_dir=.*%include_dir=$(PROTOUSRPHPVERDIR)/include/php%" \
	 > proto-scripts/php-config-proto ; \
	chmod 755 proto-scripts/php-config-proto ) ;

# need to avoid clashes in /var/tmp directory
COMPONENT_PRE_TEST_ACTION += ( rm -rf $(BUILD_DIR)/tmp-$(MACH); \
	mkdir $(BUILD_DIR)/tmp-$(MACH) );
COMPONENT_TEST_ENV += TMPDIR=$(BUILD_DIR)/tmp-$(MACH)
# test failures; keep going
COMPONENT_TEST_ARGS += -k -i
# some tests go to internet and others behave differently when proxy is set
COMPONENT_TEST_ENV += http_proxy=
COMPONENT_TEST_ENV += SKIP_ONLINE_TESTS=1
# different results for different architectures
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH)-$(BITS).master
COMPONENT_TEST_TRANSFORMS += \
    '-e "/^make/d" ' \
    '-e "/^TEST RESULT SUMMARY$$/,\$$p" ' \
    '-e "/.*/d" '

CLEAN_PATHS += proto-scripts

#clobber::
#	cd ../uw-imap; gmake clobber

# Add directory for generate check
GENERATE_PROTO_DIRS += files^files

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/libc-client
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/oniguruma
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/dtrace
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += system/network/ldap/openldap
REQUIRED_PACKAGES += text/gnu-sed
REQUIRED_PACKAGES += web/php/extension/php-imap
