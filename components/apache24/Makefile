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
# Copyright (c) 2014, 2023, Oracle and/or its affiliates.
#

BUILD_BITS= 64
COMPILER=clang
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apache2
COMPONENT_VERSION=	2.4.63
COMPONENT_BAID=		152891
COMPONENT_PROJECT_URL=	https://httpd.apache.org/
COMPONENT_SRC_NAME=	httpd
COMPONENT_ARCHIVE_HASH=	\
    sha256:1fdf1667ebe313a04e9f4d35ea9f043a4e0ebb62ba5a3047abcad824224c3867
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/httpd/$(COMPONENT_ARCHIVE)
#COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	utility/apache
COMPONENT_ANITYA_ID=	1335

CONFIGURE_DEFAULT_DIRS=no
TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# This is baked into the Apache module build configuration and is used by apxs
# to build modules.
LDFLAGS += $(CC_BITS)

# Enable adiheap and adistack security extensions
ADIHEAP_MODE = $(ADIHEAP_ENABLE)
ADISTACK_MODE = $(ADISTACK_ENABLE)

ifeq ($(strip $(OPENSSL3)),)
# We will build two separate mod_ssl versions.
COMPONENT_POST_UNPACK_ACTION = (cd $(SOURCE_DIR)/modules; $(CP) -r ssl ssl-fips-140)
PKG_MACROS +=	OPENSSL1_ONLY=
PKG_MACROS +=	OPENSSL3_ONLY=\#
else
PKG_MACROS +=	OPENSSL1_ONLY=\#
PKG_MACROS +=	OPENSSL3_ONLY=
endif

# Some patches need configure script re-creation.
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.c $(@D)/modules/aaa);
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.html $(@D)/docs/manual/mod);
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

CONFIGURE_PREFIX =	$(USRDIR)/apache2/2.4

CONFIGURE_OPTIONS +=	--enable-layout=Solaris
CONFIGURE_OPTIONS +=	--enable-mpms-shared=all
CONFIGURE_OPTIONS +=	--enable-mods-shared=all
CONFIGURE_OPTIONS +=	--enable-mods-static="unixd logio log_config watchdog version"
CONFIGURE_OPTIONS +=	--enable-proxy-fdpass
CONFIGURE_OPTIONS +=	--enable-exception-hook
CONFIGURE_OPTIONS +=	--enable-cgi
CONFIGURE_OPTIONS +=	--enable-suexec
CONFIGURE_OPTIONS +=	--enable-http2
CONFIGURE_OPTIONS +=	--with-suexec-caller=webservd
CONFIGURE_OPTIONS +=	--with-apr=$(USRDIR)/apr/1/bin/$(MACH64)/apr-1-config
CONFIGURE_OPTIONS +=	--with-apr-util=$(USRDIR)/apr-util/1/bin/$(MACH64)/apu-1-config
ifneq ($(strip $(OPENSSL3)),)
CONFIGURE_OPTIONS +=	--with-ssl=/usr/openssl/3
endif
$(SOLARIS_11_4_5_ONLY)CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
$(SOLARIS_11_3_ONLY)CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS) $(XPG6MODE)"
CONFIGURE_OPTIONS +=	LTFLAGS="--silent --tag=CC"

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
else
PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
endif

REQUIRED_PACKAGES += library/apr-1
REQUIRED_PACKAGES += library/apr-util-1
REQUIRED_PACKAGES += library/apr-util-1/apr-ldap
REQUIRED_PACKAGES += library/apr-util-1/dbd-mysql
REQUIRED_PACKAGES += library/apr-util-1/dbd-sqlite
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre2
ifeq ($(strip $(OPENSSL3)),)
REQUIRED_PACKAGES += library/security/openssl
#REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
else
REQUIRED_PACKAGES += library/security/openssl-3
endif
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
