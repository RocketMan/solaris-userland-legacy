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

# Built in SFW with gcc and builds cleanly now only with gcc
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

PATH=$(JAVA_HOME)/bin:$(USRBINDIR)

COMPONENT_NAME=			erlang
COMPONENT_VERSION=		24.2
COMPONENT_PROJECT_URL=	https://erlang.org/
COMPONENT_SRC_NAME=	otp_src
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
    sha256:0b9c9ba7d8b40f6c77d529e07561b10f0914d2bfe9023294d7eda85b62936792
COMPONENT_ARCHIVE_URL=  https://github.com/erlang/otp/archive/OTP-${COMPONENT_VERSION}.tar.gz
COMPONENT_BUGDB=	utility/erlang
COMPONENT_ANITYA_ID=	707
COMPONENT_POST_UNPACK_ACTION= ( $(MV) otp-OTP-$(COMPONENT_VERSION) $(COMPONENT_SRC))
COMPONENT_PREP_ACTION = (cd $(@D); ./otp_build update_configure)
COMPONENT_VERSION_SHORT= $(shell echo $(COMPONENT_VERSION) | cut -d'.' -f1-2)

# manpages
COMPONENT_NAME_1=	otp_doc_man
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)_$(COMPONENT_VERSION_SHORT)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:56ae4b13fc7c003f4dd9951a9ff2a0bae0b38473df2c078d79c8553c277c5f4c
COMPONENT_ARCHIVE_URL_1=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_1)
UNPACK_ARGS_1=	-r $(COMPONENT_SRC_1)
PKG_PROTO_DIRS +=	$(COMPONENT_SRC_1)
COMPONENT_ANITYA_ID_1=	707

# HTML documentation
COMPONENT_NAME_2=	otp_doc_html
COMPONENT_SRC_2=	$(COMPONENT_NAME_2)_$(COMPONENT_VERSION_SHORT)
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_HASH_2=	\
    sha256:f479cbc8a28532fd6a0a55fc26684b4e79312da4f86ee0735d0757f936672bbc
COMPONENT_ARCHIVE_URL_2=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE_2)
UNPACK_ARGS_2=	-r $(COMPONENT_SRC_2)
PKG_PROTO_DIRS +=	$(COMPONENT_SRC_2)
COMPONENT_ANITYA_ID_2=	707

COMPONENT_BAID=		116024

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)

# Unreproducible test results, many hours to finish.
$(SKIP_TEST_AT_TOP_LEVEL)

# This is just a workaround to a problem we occasionally see on sparc.
# The build stops and never finishes. The process erl_child_setup seems to be
# stuck. Erlang normally builds in about 75 minutes (one job), so 180 minutes
# timeout should be more than enough. This change makes sure that Erlang is built
# in 3 attempts and if all attempts fail, then it is almost sure that there
# is a problem in Erlang code or Common Build Environment.
GMAKE := $(WS_TOOLS)/repeat_cmd 3 3h $(GMAKE)
COMPONENT_BUILD_ENV += REPEAT_CMD_CLEANUP="gmake clean"

include $(WS_MAKE_RULES)/common.mk

# Fix 64-bit linking.
LDFLAGS += $(CC_BITS)

CXXFLAGS += -std=c++11

CONFIGURE_OPTIONS += --enable-smp-support
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --enable-fips
CONFIGURE_OPTIONS += --enable-dynamic-ssl-lib

ifneq ($(strip $(OPENSSL3)),)
CONFIGURE_OPTIONS += --with-ssl=/usr/openssl/3
# Disable disallowed cyphers (headers are not available)
CFLAGS += -DOPENSSL_NO_MD4 -DOPENSSL_NO_RC2 -DOPENSSL_NO_RC4
else
CONFIGURE_OPTIONS += --with-ssl
endif

# Disable kernel poll on sparc to avoid hangs in erl_child_setup (bug 31443512).
CONFIGURE_OPTIONS.sparc += --disable-kernel-poll

# Erlang doesn't appear to like ASLR: it uses mmap() with MAP_FIXED, and
# makes assumptions about memory layout that aren't true on Solaris x86,
# leading to segmentation faults in erlc.
ASLR_MODE =	$(ASLR_DISABLE)

# Use cp(1) instead of cloney because erlang's 'install' target uses 'tar'
# to copy files and our tar doesn't handle long links by default.  Between
# the use of 'tar' and 'ld', a path adjustment wasn't an option due to the
# need for /usr/bin/ld and /usr/gnu/bin/tar.  This is still the case with
# erlang version 17.5.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) -rp $(SOURCE_DIR)/. $(@D))
CONFIGURE_SCRIPT =		$(@D)/configure

# We need to re-run the nested configure script for the wx sub-component so
# that it will properly detect wxWidgets support by adding -std=c++11 to $(CXX)
# (workaround for the configure script ignoring CXXFLAGS) and with ERL_TOP set
# so that the wx component knows we're building inside the erlang source tree.
# run autoconf in lib/crypto to propagate the configure.in patch
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D)/lib/wx; $(ENV) $(CONFIGURE_ENV) \
		CXX="$(CXX) -std=c++11" \
		ERL_TOP="$(@D)" \
		$(CONFIG_SHELL) \
		./configure $(CONFIGURE_OPTIONS))

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=	V=1

COMPONENT_INSTALL_ARGS += INSTALL_PREFIX=$(PROTO_DIR)

# Run Erlang release tests; it takes many hours...
COMPONENT_TEST_DIR = $(COMPONENT_DIR)
COMPONENT_TEST_CMD = $(SHELL)
COMPONENT_TEST_TARGETS = run_erlang_tests.sh $(BUILD_DIR_64)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

# Some header files are architecture specific, therefore,
# we must avoid to rename some i386 directories to $(MACH).
GENERATE_TRANSFORMS := generate/pretrans $(GENERATE_TRANSFORMS)

# Extra directories with documentation for 'gmake manifest-check'.
GENERATE_PROTO_DIRS += otp_doc_man_$(COMPONENT_VERSION_SHORT)/man/ otp_doc_html_$(COMPONENT_VERSION_SHORT)/ files^files

# remove INSTALL_PREFIX from path
COMPONENT_POST_INSTALL_ACTION += \
	$(PERL) -pi -e "s|$(PROTO_DIR)||g" \
		$(PROTOUSRLIBDIR64)/erlang/bin/erl \
		$(PROTOUSRLIBDIR64)/erlang/releases/RELEASES

COMPONENT_TEST_TRANSFORMS += \
        '-e "/^run_erlang_tests.sh/d" '

REQUIRED_PACKAGES += developer/java/jdk-8
REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += library/graphics/wxwidgets-32
REQUIRED_PACKAGES += library/ncurses
ifneq ($(strip $(OPENSSL3)),)
REQUIRED_PACKAGES += library/security/openssl-3
else
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
endif
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/datalink
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libglu
REQUIRED_PACKAGES += x11/library/mesa
