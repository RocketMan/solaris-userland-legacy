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
# Copyright (c) 2014, 2022, Oracle and/or its affiliates.
#

BUILD_BITS= 64
COMPILER =	gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		postfix
COMPONENT_VERSION=	3.2.2
COMPONENT_PROJECT_URL=	http://www.postfix.org
COMPONENT_ARCHIVE_HASH=	\
    sha256:d06849418d119d09366997b2b481bb23f737629769b4e4a52da42fb3ad8b0576
COMPONENT_ARCHIVE_URL=	https://archive.mgm51.com/mirrors/$(COMPONENT_NAME)-source/official/$(COMPONENT_ARCHIVE)
#COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig
COMPONENT_ANITYA_ID=	3693

COMPONENT_BAID=		40979

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include ../../make-rules/common.mk

# The builds system would need patching in order to build with PIE
CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

# general
CCARGS =	-DDEF_DAEMON_DIR=\\\"/usr/lib/postfix\\\"
CCARGS +=	-DDEF_MANPAGE_DIR=\\\"/usr/share/man\\\"
CCARGS +=	-DDEF_NEWALIAS_PATH=\\\"/usr/sbin/newaliases\\\"
# TLS
CCARGS +=	-DUSE_TLS
AUXLIBS =	-lssl -lcrypto
# Berkeley DB
CCARGS +=	-DHAS_DB
AUXLIBS +=	-ldb-5.3
# SQLite
CCARGS +=	-DHAS_SQLITE
AUXLIBS +=	-lsqlite3
# LDAP
CCARGS +=	-DHAS_LDAP -I/usr/include/openldap
AUXLIBS +=	-lldap_r-2.4 -llber-2.4
# Cyrus SASL
CCARGS +=	-DUSE_SASL_AUTH -DUSE_CYRUS_SASL -I/usr/include/sasl
$(SOLARIS_11_4_5_ONLY)AUXLIBS +=	-lsasl2
$(SOLARIS_11_3_ONLY)AUXLIBS +=	-lsasl

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

# pcre-config is run as part of the setup, so we need to find the 64-bit
# version so it will provide a 64-bit runpath, o/w pkglint gives warnings.
PATH =		$(USRBINDIR64):$(USRBINDIR):$(GNUBIN)

COMPONENT_BUILD_ENV += CCARGS="$(CCARGS)"
COMPONENT_BUILD_ENV += OPT="$(CFLAGS)"
COMPONENT_BUILD_ENV += DEBUG="$(CFLAGS)"
COMPONENT_BUILD_ENV += PATH="$(PATH)"
COMPONENT_BUILD_ENV += AUXLIBS="$(AUXLIBS)"
# Postfix build deliberately fails if LD_LIBRARY_PATH is set
COMPONENT_BUILD_ENV += LD_LIBRARY_PATH=

COMPONENT_INSTALL_TARGETS = non-interactive-package install_root="$(PROTO_DIR)"

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/icu
$(SOLARIS_11_3_ONLY)REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += system/library/security/libsasl2
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += system/network/ldap/openldap
