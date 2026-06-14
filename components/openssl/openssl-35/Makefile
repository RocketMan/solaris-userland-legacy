#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2024 Marcel Telka
# Copyright 2026 Jim Mason adapted for Solaris 11.3
#

BUILD_BITS=64_and_32
COMPILER=gcc

include ../../../make-rules/shared-macros.mk

# in case /usr/bin/pod2man is not mediated in 11.3
$(SOLARIS_11_3_ONLY)PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/$(PERL_VERSION)/bin

COMPONENT_NAME=			openssl
COMPONENT_VERSION=		3.5.7
COMPONENT_PROJECT_URL=		https://openssl-library.org/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		https://github.com/openssl/openssl/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:a8c0d28a529ca480f9f36cf5792e2cd21984552a3c8e4aa11a24aa31aeac98e8

include $(WS_MAKE_RULES)/common.mk

# API/ABI incompatible changes are introduced with MAJOR version number change.
# See also https://openssl-library.org/policies/releasestrat/index.html
OPENSSL_VERSION = $(firstword $(subst ., ,$(COMPONENT_VERSION)))

OPENSSL_PREFIX= $(USRDIR)/openssl/$(OPENSSL_VERSION)
OPENSSL_BINDIR.64= $(OPENSSL_PREFIX)/bin
OPENSSL_BINDIR.32= $(OPENSSL_PREFIX)/bin/$(MACH32)
OPENSSL_BINDIR= $(OPENSSL_BINDIR.$(BITS))
OPENSSL_LIBDIR.64= $(OPENSSL_PREFIX)/lib/$(MACH64)
OPENSSL_LIBDIR.32= $(OPENSSL_PREFIX)/lib
OPENSSL_LIBDIR= $(OPENSSL_LIBDIR.$(BITS))
OPENSSL_PKG_CONFIG_PATH.32= $(OPENSSL_PREFIX)/lib/pkgconfig
OPENSSL_PKG_CONFIG_PATH.64= $(OPENSSL_PREFIX)/lib/$(MACH64)/pkgconfig
OPENSSL_PKG_CONFIG_PATH= $(OPENSSL_PKG_CONFIG_PATH.$(BITS))
OPENSSL_INCDIR=$(OPENSSL_PREFIX)/include
OPENSSL_ETCDIR=$(ETCDIR)/openssl/$(OPENSSL_VERSION)

# OpenSSL uses Configure incompatible with autoconf
CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure
CONFIGURE_OPTIONS =
CONFIG_SHELL =

# Installation directories
CONFIGURE_OPTIONS += --openssldir=$(OPENSSL_ETCDIR)
CONFIGURE_OPTIONS += --prefix=$(OPENSSL_PREFIX)

# Define compiler and linker option sets.
# See Configurations/10-main.conf for more information.
CONFIGURE_OPTIONS32_i386 =	solaris-x86-gcc
CONFIGURE_OPTIONS32_sparc =	solaris-sparcv9-gcc
CONFIGURE_OPTIONS64_i386 =	solaris64-x86_64-gcc
CONFIGURE_OPTIONS64_sparc =	solaris64-sparcv9-gcc
CONFIGURE_OPTIONS +=		$(CONFIGURE_OPTIONS$(BITS)_$(MACH))

# Use non-default man pages suffix
COMPONENT_INSTALL_ARGS += MANSUFFIX=openssl

# We do not need to install overlapping docs, /etc, and other common files for
# 32-bit build.  We will use such files as produced by the 64-bit build.  See
# the toplevel Makefile in the build dir for more information.
#
# List of skipped targets:
# install_ssldirs	- $(OPENSSL_ETCDIR)
# install_docs		- man pages and html docs
# install_runtime	- runtime (in bin)
$(BUILD_DIR_32)/.installed: COMPONENT_INSTALL_TARGETS = install_dev install_engines install_modules

# Save includes installed during the 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += \
	$(MV) $(PROTO_DIR)/$(OPENSSL_INCDIR) $(PROTO_DIR)/$(OPENSSL_INCDIR)-32 ;

# Merge includes for 32-bit and 64-bit.  When a file differs create a wrapper.
COMPONENT_POST_INSTALL_ACTION.64 += \
	( cd $(PROTO_DIR)/$(OPENSSL_INCDIR)/.. ; \
	nd=$(notdir $(OPENSSL_INCDIR)) ; \
	for f in $$($(ENV) $(GDIFF) -qr $$nd-32 $$nd \
	    | $(GSED) -n -e 's|^Files .* '"$$nd"'/\([^ ]\{1,\}\) differ$$|\1|p') ; do \
		f32=$$f-32 ; f64=$$f-64 ; \
		[ "$${f\#\#*.}" != "$$f" ] \
			&& f32=$${f%.*}-32.$${f\#\#*.} && f64=$${f%.*}-64.$${f\#\#*.} ; \
		[ -e "$$nd/$$f32" ] && exit 1 ; \
		[ -e "$$nd/$$f64" ] && exit 1 ; \
		$(MV) $$nd/$$f $$nd/$$f64 ; \
		$(MV) $$nd-32/$$f $$nd/$$f32 ; \
		printf '\#if defined (__amd64)\n\#include <%s>\n\#else\n\#include <%s>\n\#endif\n' \
		    "$$f64" "$$f32" > $$nd/$$f ; \
	done ) ; \
	$(RM) -r $(PROTO_DIR)/$(OPENSSL_INCDIR)-32 ;

# Provide usable openssl.cnf
COMPONENT_POST_INSTALL_ACTION.64 += $(GSED) -i \
	-e 's|\(^dir.*=.*\)\./demoCA\(.*Where everything is kept.*\)$$|\1$(OPENSSL_ETCDIR)\2|' \
	-e 's/^crlnumber/\#&/' \
	-e 's/^countryName_default/\#&/' \
	-e 's/^stateOrProvinceName_default/\#&/' \
	-e 's/^0\.organizationName_default/\#&/' \
	$(PROTO_DIR)/$(OPENSSL_ETCDIR)/openssl.cnf ;

# Move programs to the bin directory so they are directly available
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(MV) $(PROTO_DIR)/$(OPENSSL_ETCDIR)/misc/* $(PROTO_DIR)/$(OPENSSL_BINDIR) ;

define create-symlinks
	for f in $(1:%=$(PROTO_DIR)/%) ; do \
		[ -e "$$f" ] || continue ; \
		t=$(PROTO_DIR)/$(2) ; \
		while true ; do \
			while [ "$${f#/}" != "$$f" ] ; do f=$${f#/} ; done ; \
			while [ "$${t#/}" != "$$t" ] ; do t=$${t#/} ; done ; \
			[ "$${f%%/*}" == "$${t%%/*}" ] || break ; \
			f=$${f#$${f%%/*}} ; \
			t=$${t#$${t%%/*}} ; \
		done ; \
		[ "$$t" ] && t=$$t/ ; \
		f=$$(echo $$t | $(GSED) -e 's|[^/]\{1,\}|..|g')$$f ; \
		$(MKDIR) $(PROTO_DIR)/$(2) ; \
		$(SYMLINK) $$f $(PROTO_DIR)/$(2)/$$(basename $$f)$(3) ; \
	done
endef

# Create various symlinks at standard locations
COMPONENT_POST_INSTALL_ACTION += $(call create-symlinks,$(OPENSSL_LIBDIR)/*.so*,$(USRLIBDIR.$(BITS))) ;
COMPONENT_POST_INSTALL_ACTION += $(call create-symlinks,$(OPENSSL_PKG_CONFIG_PATH)/*,$(PKG_CONFIG_PATH.$(BITS))) ;
COMPONENT_POST_INSTALL_ACTION += $(call create-symlinks,$(OPENSSL_LIBDIR)/cmake/*,$(USRLIBDIR.$(BITS))/cmake) ;
COMPONENT_POST_INSTALL_ACTION.64 += $(call create-symlinks,$(OPENSSL_BINDIR)/*,$(USRBINDIR)) ;
COMPONENT_POST_INSTALL_ACTION.64 += $(call create-symlinks,$(OPENSSL_INCDIR)/*,$(USRINCDIR)) ;
COMPONENT_POST_INSTALL_ACTION.64 += $(SYMLINK) $(OPENSSL_VERSION) $(PROTOETCDIR)/openssl/default ;

# Compatibility symlink for 64 bit libraries
COMPONENT_POST_INSTALL_ACTION.64 += $(SYMLINK) $(MACH64) $(PROTO_DIR)/$(OPENSSL_LIBDIR)/../64 ;

# Convert the (empty) certs directory to a symlink
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(MV) $(PROTO_DIR)/$(OPENSSL_ETCDIR)/certs $(PROTO_DIR)/$(OPENSSL_ETCDIR)/.. ; \
	$(SYMLINK) ../certs $(PROTO_DIR)/$(OPENSSL_ETCDIR)/certs ;

# Fix shebang for Perl scripts
COMPONENT_POST_INSTALL_ACTION.64 += \
	for f in $(PROTO_DIR)/$(OPENSSL_BINDIR)/* ; do \
		[ -L $$f ] && continue ; \
		[ -f $$f ] || continue ; \
		$(GSED) -i -e '1s|^\(\#!/usr/bin/\)env \(perl\)$$|\1\2|' $$f ; \
	done ;

# See test/README.md
COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Test transforms
COMPONENT_TEST_TRANSFORMS += '-e "0,/run_tests\.pl/d"'		# delete any lines up through run_tests.pl
COMPONENT_TEST_TRANSFORMS += '-e "s/,  *[0-9]* wallclock.*//"'	# delete timings
COMPONENT_TEST_TRANSFORMS += '-e "/^make\[/d"'			# delete make logs

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-$(PERL_VERSION_NODOT)
REQUIRED_PACKAGES += system/library
