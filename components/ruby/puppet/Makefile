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
# Copyright (c) 2013, 2023, Oracle and/or its affiliates.
#
include ../../../make-rules/shared-macros.mk

# Puppet and its modules are built to use the currently
# supported version of Ruby runtime only.
RUBY_VERSIONS = $(RUBY_PUPPET_VERSION)

GIT_REPO= https://github.com/puppetlabs/puppet
GIT_COMMIT_ID=  7.21.0
GIT_HASH=sha256:d5883666e7bc6872e00ec98fbeb1af1adc4b36ee9e3ada2a0800cc71765d5fa4

COMPONENT_NAME=		puppet
COMPONENT_VERSION=	$(GIT_COMMIT_ID)
COMPONENT_PROJECT_URL=	http://puppetlabs.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_BUGDB=	utility/puppet
COMPONENT_ANITYA_ID=	7018
COMPONENT_BAID=		136905

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/install.rb.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/ruby.mk

# puppet requires facter and hiera as part of the install phase
FACTER_LIB=$(WS_TOP)/components/ruby/facter/build/$(MACH)-$(RUBY_PUPPET_VERSION)/lib
HIERA_LIB=$(WS_TOP)/components/ruby/hiera/build/$(MACH)-$(RUBY_PUPPET_VERSION)/lib

# Puppet invokes facter methods during install phase. facter 4.x has runtime dependencies on hocon, thor and ffi.
HOCON_LIB=$(WS_TOP)/components/ruby/hocon/build/$(MACH)-$(RUBY_PUPPET_VERSION)/lib
THOR_LIB=$(WS_TOP)/components/ruby/thor/build/$(MACH)-$(RUBY_PUPPET_VERSION)/lib
FFI_C_LIB=$(WS_TOP)/components/ruby/ffi/build/prototype/$(MACH)/$(VENDOR_GEM_DIR)/gems/ffi-1.13.1/lib
FFI_LIB=$(WS_TOP)/components/ruby/ffi/build/$(MACH)-$(RUBY_PUPPET_VERSION)/lib

COMPONENT_INSTALL_ENV	+= RUBYLIB="$(FFI_C_LIB):$(FFI_LIB):$(HOCON_LIB):$(FACTER_LIB):$(HIERA_LIB):$(THOR_LIB)"

../facter/build/%/.installed:
	cd ../facter ; $(GMAKE) install

../hiera/build/%/.installed:
	cd ../hiera ; $(GMAKE) install


SECURITY_FILES=$(addprefix files/,auth_attr exec_attr prof_attr)
ETC_FILES=$(addprefix files/,user_attr)

ext/PuppetAudit.so:
	# Ruby extension for auditing
	cd ext; $(RUBY) extconf.rb; $(GMAKE)

clean::
	@if [ -f ext/Makefile ]; then \
		cd ext; $(GMAKE) clean; $(RM) Makefile; \
	fi

$(BUILD_DIR)/puppet.conf: ext/PuppetAudit.so
	RUBYLIB=$(PROTO_DIR)/usr/ruby/$(RUBY_VERSION):$(PROTO_DIR)/$(VENDOR_RUBY):$(COMPONENT_DIR)/ext \
	  $(PROTO_DIR)/usr/sbin/puppet agent --genconfig > $@

$(PROTOSVCMANIFESTDIR)/application/puppet.xml: $(BUILD_DIR)/puppet.conf
	-$(RM) $@
	$(MKDIR) $(PROTOSVCMANIFESTDIR)/application
	$(PYTHON.3.11) tools/update_smf.py -c $(BUILD_DIR)/puppet.conf \
	  -s files/puppet.xml.stub -o $@
	/usr/sbin/svccfg validate $@

# Collect and print puppet module manifests for cherry picking into group
# dependencies as a helper for the package maintainer
PUPPET_MODULE_MANIFESTS = $(sort $(wildcard $(WS_TOP)/components/ruby/puppet-modules/*-*/*.p5m))
print-modules: $(PUPPET_MODULE_MANIFESTS)
	$(PKGMOGRIFY) -i -O /dev/null $(WS_TRANSFORMS)/group-dependency $(PUPPET_MODULE_MANIFESTS)


# set the bindir to /usr/sbin
INSTALL_RB_BINDIR_OPTION =	--bindir=$(USRSBINDIR)

# --sbindir option not supported by Puppet install.rb
INSTALL_RB_SBINDIR_OPTION =

INSTALL_RB_OPTIONS += --vardir=/var/cache/puppetlabs \
	                  --localedir=/usr/puppetlabs/puppet/share/locale

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PKG_OPTIONS +=	-I $(BUILD_DIR)

# common targets
build::		$(BUILD_NO_ARCH)

# make sure facter and hiera are installed first
install:	../facter/build/$(MACH)-$(RUBY_PUPPET_VERSION)/.installed \
			../hiera/build/$(MACH)-$(RUBY_PUPPET_VERSION)/.installed \
			$(INSTALL_NO_ARCH) ext/PuppetAudit.so $(PROTOSVCMANIFESTDIR)/application/puppet.xml

# puppet requires the installation of the following rubygems to run
# the unittests:  rspec rspec-expectations mocha rack rgen
# Disable the tests until these rubygems are available.
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += runtime/ruby-$(RUBY_PUPPET_NODOT_VERSION)
REQUIRED_PACKAGES += library/ruby/hiera
REQUIRED_PACKAGES += library/ruby/semantic_puppet
REQUIRED_PACKAGES += library/ruby/concurrent-ruby
REQUIRED_PACKAGES += library/ruby/deep_merge
REQUIRED_PACKAGES += system/management/facter
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
