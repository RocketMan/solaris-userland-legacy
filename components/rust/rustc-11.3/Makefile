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
# Copyright (c) 2020-2024 Jim Mason <jmason at ibinx dot com>.
#
# Adapted from original code Copyright (c) 2018, 2020, Oracle and/or its
# affiliates. All rights reserved.
#

BUILD_BITS =	64
COMPILER =	gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	rustc
COMPONENT_VERSION =	1.78.0
COMPONENT_SRC =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_PROJECT_URL =	http://www.rust-lang.org/
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH = \
    sha256:8065824f0255faa3901db8206e6f9423f6f8c07cec28bc6f2797c6c948310ece

COMPONENT_ARCHIVE_URL =	https://static.rust-lang.org/dist/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL =	$(COMPONENT_ARCHIVE_URL).asc

COMPONENT_BUGDB =	utility/rust
COMPONENT_ANITYA_ID =	7635

PKG_VARS += RUST_PLATFORM

# Workaround for https://github.com/rust-lang/rust/issues/74551
ifeq ($(MACH), sparc)
ADDITIONAL_PATCHES += patches/Bug74551.patch-SPARC
endif

include $(WS_MAKE_RULES)/common.mk

$(SOURCE_DIR_crates)/.patched: PATCH_LEVEL=0

# Everything expects GNU utilities, so make sure those are preferred.
PATH = $(COMPONENT_DIR)/epoll:/usr/gnu/bin:/usr/bin

# LD_B_DIRECT breaks the build.
LD_B_DIRECT =

RUST_PLATFORM = $(MACH64:amd64=x86_64)-pc-solaris

# The configure Rust uses isn't autoconf; it's hand-rolled, and doesn't
# recognize all the autoconf options, so we start from scratch.
CONFIGURE_OPTIONS =	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--default-linker=gcc
CONFIGURE_OPTIONS +=	--enable-local-rust
CONFIGURE_OPTIONS +=	--disable-llvm-static-stdcpp
CONFIGURE_OPTIONS +=	--disable-docs
CONFIGURE_OPTIONS +=	--disable-compiler-docs
CONFIGURE_OPTIONS +=	--disable-cargo-native-static
CONFIGURE_OPTIONS +=	--enable-llvm-link-shared
CONFIGURE_OPTIONS +=	--llvm-root=$(CONFIGURE_PREFIX)
# from 1.71.0, the following is needed to use the system llvm
CONFIGURE_OPTIONS +=	--build=$(RUST_PLATFORM)

ifeq ($(strip $(OPENSSL3)),)
# From rust 1.75.0, OpenSSL 1.x or later is required
OPENSSL_LIB_DIR=/usr/openssl/1.1/lib/64
OPENSSL_INCLUDE_DIR=/usr/openssl/1.1/include
else
# Use OpenSSL 3
OPENSSL_LIB_DIR=/usr/openssl/3/lib/64
OPENSSL_INCLUDE_DIR=/usr/openssl/3/include
endif

COMPONENT_BUILD_ENV += OPENSSL_LIB_DIR=$(OPENSSL_LIB_DIR)
COMPONENT_BUILD_ENV += OPENSSL_INCLUDE_DIR=$(OPENSSL_INCLUDE_DIR)
COMPONENT_INSTALL_ENV += OPENSSL_LIB_DIR=$(OPENSSL_LIB_DIR)
COMPONENT_INSTALL_ENV += OPENSSL_INCLUDE_DIR=$(OPENSSL_INCLUDE_DIR)

# From rust 1.76.0, it is not picking up OPENSSL_LIB_DIR, so we force it
COMPONENT_PRE_CONFIGURE_ACTION += \
       ( cd $(COMPONENT_DIR)/epoll; \
       $(GCC_ROOT)/bin/gcc -shared -DDEBUG=0 -o libepoll.so -fPIC -c epoll.c ; \
       $(GCC_ROOT)/bin/gcc -DDEBUG=0 -fPIC -c compat.c ; \
       ar rcs libcompat.a compat.o ; \
       echo "\#!/bin/sh" > gcc ; \
       echo "$(GCC_ROOT)/bin/gcc -L$(OPENSSL_LIB_DIR) \$$@ -L$(COMPONENT_DIR)/epoll -lepoll -lcompat" >> gcc ; \
       chmod a+x gcc ) ;

CLEAN_PATHS += epoll/compat.o
CLEAN_PATHS += epoll/libcompat.a
CLEAN_PATHS += epoll/libepoll.so
CLEAN_PATHS += epoll/gcc

VENDORED_SOURCES_ENFORCE = \
        cd $(BUILD_DIR); mkdir -p .cargo; \
        echo "[source.crates-io]" > .cargo/config; \
        echo "replace-with = \"vendored-sources\"" >> .cargo/config; \
        echo "[source.vendored-sources]" >> .cargo/config; \
        echo "directory = \"$(SOURCE_DIR)/vendor\"" >> .cargo/config;

COMPONENT_PRE_BUILD_ACTION = $(VENDORED_SOURCES_ENFORCE)

# Put the bits cargo downloads in a private directory.  This could be cached
# somewhere more permanent, but it's important to make sure that a person's
# $HOME/.cargo isn't used.
COMPONENT_BUILD_ENV +=	CARGO_HOME=$(BUILD_DIR)/.cargo
COMPONENT_INSTALL_ENV +=	CARGO_HOME=$(BUILD_DIR)/.cargo
COMPONENT_TEST_ENV +=	CARGO_HOME=$(BUILD_DIR)/.cargo

ifneq ($(strip $(OPENSSL3)),)
COMPONENT_PRE_BUILD_ACTION += \
	( $(MKDIR) $(@D)/pkgconfig-my; \
	$(GSED) 's;-L.* ;;' $(USRLIBDIR)/64/pkgconfig/zlib.pc > $(@D)/pkgconfig-my/zlib.pc ) ;
PKG_CONFIG_PATHS += $(@D)/pkgconfig-my
endif

# Rust library names contain hash which differs between intel and sparc.
# Therefore library list need to be created to be included into p5m file.
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTO_DIR); \
	ls -1 usr/lib/lib* \
	  usr/lib/rustlib/$(MACH64:amd64=x86_64)-pc-solaris/codegen-backends/lib* \
	  usr/lib/rustlib/$(MACH64:amd64=x86_64)-pc-solaris/lib/lib* | \
	  awk '{ print "file path="$$1 " variant.arch=$(MACH)" }' > ../../libraries-hashed.$(MACH64); )

# pkg-report requires *.p5m files to be processed by pkgmogrify. Since the
# libraries-hashed normally comes from build and since pkg-report runs
# 'gmake clean' first we have to create empty file instead.
PKG_REPORT_ADDITIONAL_SETUP = touch $(BUILD_DIR)/libraries-hashed.$(MACH64)

# We put $(BOOTSTRAP_DIR)/usr/bin into $PATH if we used it because we need to
# use the same compiler during test as we did during build.  Otherwise, we'll
# end up rebuilding the world.
COMPONENT_TEST_ENV +=	PATH=$(BOOTSTRAP_DIR:%=%/usr/bin:)$(PATH)
COMPONENT_TEST_CMD =	$(PYTHON) $(SOURCE_DIR)/x.py
COMPONENT_TEST_ARGS =	test --no-fail-fast -j 8
COMPONENT_TEST_TARGETS =

REQUIRED_PACKAGES += developer/llvm/llvm
REQUIRED_PACKAGES += developer/llvm/llvm-libs
REQUIRED_PACKAGES += developer/rust/rustc
REQUIRED_PACKAGES += library/libssh2
ifneq ($(strip $(OPENSSL3)),)
REQUIRED_PACKAGES += library/security/openssl-3
else
REQUIRED_PACKAGES += library/security/openssl-11
endif
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
