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
# Copyright (c) 2011, 2022, Oracle and/or its affiliates.
#
BUILD_BITS= 64_and_32
COMPILER=gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME        = graphviz
COMPONENT_VERSION     = 2.47.1
COMPONENT_PROJECT_URL = http://www.graphviz.org/
COMPONENT_SRC         = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE     = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:513765332d45c3e4ddc539aed4bbaf536e86bd87946d3fea25201c3cb7afc31a
COMPONENT_ARCHIVE_URL = \
    http://gitlab.com/graphviz/graphviz/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID   = 1249

COMPONENT_BAID = 100932

COMPONENT_PREP_ACTION += \
	( cd $(@D) ; PATH="$(PATH)" $(CONFIG_SHELL) autogen.sh NOCONFIG)

# publish for only one version of perl
PERL_VERSIONS = $(PERL_VERSION)

# We want to build a couple of extra things after the installs are done, so set
# the install targets appropriately.
INSTALL_TARGET = $(INSTALL_$(MK_BITS))
INSTALL_TARGET += $(PROTOUSRLIBDIR)/graphviz/config6
INSTALL_TARGET += $(PROTO_DIR)/$(PYTHON.3.7.VENDOR_PACKAGES)/gv.pyc
INSTALL_TARGET += $(PROTO_DIR)/$(PYTHON.3.9.VENDOR_PACKAGES)/gv.pyc
INSTALL_TARGET += $(PROTO_DIR)/$(PYTHON.3.11.VENDOR_PACKAGES)/gv.pyc

include $(WS_MAKE_RULES)/common.mk

PATH =		/usr/php/8.2/bin:/usr/bin:/usr/gnu/bin

# GMP header files for the guile extension (no --with- flag)
# The guile build is broken with studio (15732452), so we disable this for now.
# CPPFLAGS +=	-I/usr/include/gmp
# Java header files (--with-javaincludedir allows for only one directory)
CPPFLAGS +=	-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/solaris

$(SOLARIS_11_3_ONLY)LDFLAGS += -lsocket -lnsl

# Make sure to use the right python, depending on the 32/64-bit build.
CONFIGURE_ENV +=	PYTHON3=$(PYTHON.3.9)
CONFIGURE_OPTIONS +=	--without-included-ltdl
CONFIGURE_OPTIONS +=    --with-qt=no
CONFIGURE_OPTIONS +=	--enable-go=no
CONFIGURE_OPTIONS +=	--enable-ocaml=no
CONFIGURE_OPTIONS +=	--enable-python=no
CONFIGURE_OPTIONS +=	--enable-python2=no
CONFIGURE_OPTIONS +=	--enable-python3=yes
CONFIGURE_OPTIONS +=	--enable-tcl=yes
CONFIGURE_OPTIONS +=	--x-libraries=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	--with-gdincludedir=$(USRINCDIR)/gd2
CONFIGURE_OPTIONS +=	--enable-man-pdfs

# Makefile.am files of this component are not compatible with Solaris make.
# Use GNU make to avoid the configuration error when makefile fragments are processed.
CONFIGURE_OPTIONS +=  MAKE=$(GMAKE)

COMPONENT_BUILD_ARGS += 	GREP=$(USRBINDIR)/ggrep

# perl, ruby, php ship 64-bit only.
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--enable-perl=no
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--enable-ruby=no
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--enable-php=no
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--with-rsvg=no
$(CONFIGURE_64): CONFIGURE_ENV +=	PERL=$(PERL)
$(CONFIGURE_64): CONFIGURE_ENV +=	RUBY=$(RUBY.3.1)
$(INSTALL_64): COMPONENT_INSTALL_ARGS += PHP_INSTALL_DIR=$(shell PATH=$(PATH) php-config --extension-dir)
# tcl ships both 32 and 64 bit, but even though /usr/bin/tclsh is 64-bit, there
# is no place to stick 64-bit modules, so skip it.  On the other hand, make
# sure to find the right tcl bits when building 32-bit.
$(CONFIGURE_32): CONFIGURE_OPTIONS +=	--with-tclsh=$(USRBINDIR)/$(MACH32)/tclsh
$(CONFIGURE_32): CONFIGURE_ENV += 	TCLCONFIG=$(USRLIBDIR)/tclConfig.sh
$(CONFIGURE_64): CONFIGURE_OPTIONS +=	--with-tclsh=$(USRBINDIR)/tclsh
$(CONFIGURE_64): CONFIGURE_ENV += 	TCLCONFIG=$(USRLIBDIR)/$(MACH64)/tclConfig.sh
# Put the 64-bit lua module in a 64-bit directory.
$(INSTALL_32): COMPONENT_INSTALL_ARGS += LUA_INSTALL_DIR=$(USRLIBDIR)/lua/5.4
$(INSTALL_64): COMPONENT_INSTALL_ARGS += LUA_INSTALL_DIR=$(USRLIBDIR)/lua/5.4/64
# Use GNU ln, which supports the -r (--relative) option.
COMPONENT_INSTALL_ARGS += LN_S="gln -s"

# build php and python modules for older versions as well
PHP_74_CONFIG = /usr/php/7.4/bin/php-config
PHP_74_INCLUDES := $(shell $(PHP_74_CONFIG) --includes)
PHP_74_INSTALL_DIR := $(shell $(PHP_74_CONFIG) --extension-dir)
PHP_74_LDFLAGS := $(shell $(PHP_74_CONFIG) --ldflags)
PHP_74_LIBS := $(shell $(PHP_74_CONFIG) --libs)
PHP_80_CONFIG = /usr/php/8.0/bin/php-config
PHP_80_INCLUDES := $(shell $(PHP_80_CONFIG) --includes)
PHP_80_INSTALL_DIR := $(shell $(PHP_80_CONFIG) --extension-dir)
PHP_80_LDFLAGS := $(shell $(PHP_80_CONFIG) --ldflags)
PHP_80_LIBS := $(shell $(PHP_80_CONFIG) --libs)
PHP_81_CONFIG = /usr/php/8.1/bin/php-config
PHP_81_INCLUDES := $(shell $(PHP_81_CONFIG) --includes)
PHP_81_INSTALL_DIR := $(shell $(PHP_81_CONFIG) --extension-dir)
PHP_81_LDFLAGS := $(shell $(PHP_81_CONFIG) --ldflags)
PHP_81_LIBS := $(shell $(PHP_81_CONFIG) --libs)

PKG_CONFIG = /usr/bin/pkg-config
PYTHON_37_INCLUDES := $(shell $(PKG_CONFIG) --cflags python-3.7)
PYTHON_37_LIBS = $(shell $(PKG_CONFIG) --libs python-3.7)
PYTHON_37_INSTALL_DIR := /usr/lib/python3.7/vendor-packages
PYTHON_311_INCLUDES := $(shell $(PKG_CONFIG) --cflags python-3.11)
PYTHON_311_LIBS = $(shell $(PKG_CONFIG) --libs python-3.11)
PYTHON_311_INSTALL_DIR := /usr/lib/python3.11/vendor-packages

$(CONFIGURE_64): COMPONENT_POST_CONFIGURE_ACTION += \
    (cd $(@D) ; cp -rp tclpkg/gv tclpkg/gv-additional ; \
    $(GSED) -i '/^SUBDIRS =/s|$$| gv-additional|' tclpkg/Makefile ; \
    $(GSED) -i \
     -e '/^PHP_INCLUDES =/s|=.*$$|= $(PHP_74_INCLUDES)|' \
     -e '/^PHP_INSTALL_DIR =/s|=.*$$|= $(PHP_74_INSTALL_DIR)|' \
     -e '/^PHP_LIBS =/s|=.*$$|= $(PHP_74_LDFLAGS) $(PHP_74_LIBS)|' \
     -e '/^PYTHON3 =/s|=.*$$|= $(PYTHON.3.7)|' \
     -e '/^PYTHON3_INCLUDES =/s|=.*$$|= $(PYTHON_37_INCLUDES)|' \
     -e '/^PYTHON3_INSTALL_DIR =/s|=.*$$|= $(PYTHON_37_INSTALL_DIR)|' \
     -e '/^PYTHON3_LIBS =/s|=.*$$|= $(PYTHON_37_LIBS)|' \
     `find tclpkg/gv-additional -name Makefile` ) ; \
    (cd $(@D) ; cp -rp tclpkg/gv tclpkg/gv-additionalx ; \
    $(GSED) -i '/^SUBDIRS =/s|$$| gv-additionalx|' tclpkg/Makefile ; \
    $(GSED) -i \
     -e '/^PHP_INCLUDES =/s|=.*$$|= $(PHP_80_INCLUDES)|' \
     -e '/^PHP_INSTALL_DIR =/s|=.*$$|= $(PHP_80_INSTALL_DIR)|' \
     -e '/^PHP_LIBS =/s|=.*$$|= $(PHP_80_LDFLAGS) $(PHP_80_LIBS)|' \
     -e '/^PYTHON3 =/s|=.*$$|= $(PYTHON.3.11)|' \
     -e '/^PYTHON3_INCLUDES =/s|=.*$$|= $(PYTHON_311_INCLUDES)|' \
     -e '/^PYTHON3_INSTALL_DIR =/s|=.*$$|= $(PYTHON_311_INSTALL_DIR)|' \
     -e '/^PYTHON3_LIBS =/s|=.*$$|= $(PYTHON_311_LIBS)|' \
     `find tclpkg/gv-additionalx -name Makefile` ) ;


$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION += \
    (cd $(@D)/tclpkg/gv-additional ; gmake V=1 libgv_python3.la ) ; \
    (cd $(@D)/tclpkg/gv-additionalx ; gmake V=1 libgv_python3.la ) ;

# correctly install multiple Python bindings into the corresponding
# vendor-packages directories.
37_VENDOR_PROTO := $(PROTO_DIR)$(PYTHON.3.7.VENDOR_PACKAGES)
39_VENDOR_PROTO := $(PROTO_DIR)$(PYTHON.3.9.VENDOR_PACKAGES)
311_VENDOR_PROTO := $(PROTO_DIR)$(PYTHON.3.11.VENDOR_PACKAGES)

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION += \
	($(RM) -r $(37_VENDOR_PROTO); $(MKDIR) $(37_VENDOR_PROTO); \
	$(RM) -r $(39_VENDOR_PROTO); $(MKDIR) $(39_VENDOR_PROTO); \
	$(RM) -r $(311_VENDOR_PROTO); $(MKDIR) $(311_VENDOR_PROTO); \
	$(INSTALL) -m 644 $(@D)/tclpkg/gv-additional/gv.py $(37_VENDOR_PROTO)/gv.py ; \
	$(INSTALL) $(@D)/tclpkg/gv-additional/.libs/libgv_python3.soT $(37_VENDOR_PROTO)/_gv.cpython-37m.so; \
	$(INSTALL) -m 644 $(@D)/tclpkg/gv/gv.py $(39_VENDOR_PROTO)/gv.py ; \
	$(INSTALL) $(@D)/tclpkg/gv/.libs/libgv_python3.soT $(39_VENDOR_PROTO)/_gv.cpython-39.so; \
	$(INSTALL) -m 644 $(@D)/tclpkg/gv-additionalx/gv.py $(311_VENDOR_PROTO)/gv.py ; \
	$(INSTALL) $(@D)/tclpkg/gv-additionalx/.libs/libgv_python3.soT $(311_VENDOR_PROTO)/_gv.cpython-311.so; ) ;

# Create the config file once the 32-bit build is complete.  This runs the bits
# we just built, so we have to set a handful of variables to the right place.
# The 32-bit executables are in their own directory, so we have to point to
# that version of dot explicitly.
$(PROTOUSRLIBDIR)/graphviz/config6: $(INSTALL_32)
	env LD_LIBRARY_PATH=$(PROTOUSRLIBDIR) GVBINDIR=$(PROTOUSRLIBDIR)/graphviz \
		$(PROTOUSRBINDIR)/$(MACH32)/dot -c

# Once the build is complete, compile the .py file.  There's no need to compile
# the one in the "64" directory, so don't recurse.  And make sure that the
# build path doesn't get embedded in the .pyc file.
$(PROTO_DIR)/$(PYTHON.3.7.VENDOR_PACKAGES)/gv.pyc: $(INSTALL_64)
	$(PYTHON.3.7) -m compileall -l -d $(PYTHON.3.7.VENDOR_PACKAGES) \
		$(PROTO_DIR)/$(PYTHON.3.7.VENDOR_PACKAGES)
$(PROTO_DIR)/$(PYTHON.3.9.VENDOR_PACKAGES)/gv.pyc: $(INSTALL_64)
	$(PYTHON.3.9) -m compileall -l -d $(PYTHON.3.9.VENDOR_PACKAGES) \
		$(PROTO_DIR)/$(PYTHON.3.9.VENDOR_PACKAGES)
$(PROTO_DIR)/$(PYTHON.3.11.VENDOR_PACKAGES)/gv.pyc: $(INSTALL_64)
	$(PYTHON.3.11) -m compileall -l -d $(PYTHON.3.11.VENDOR_PACKAGES) \
		$(PROTO_DIR)/$(PYTHON.3.11.VENDOR_PACKAGES)

# 'gvpr' uses HOSTCC variable instead of our configured compiler and options so
# PIE build fails. This is a workaround for that.
COMPONENT_BUILD_ARGS += HOSTCC='$(CC) $(CC_PIC_ENABLE)'

PKG_MACROS += PERL_PKG=$(PERL_PKG)
PKG_MACROS += PERL_VERSION_NODOT=$(PERL_VERSION_NODOT)

# The test infrastructure doesn't run in a VPATHed environment.
COMPONENT_PRE_TEST_ACTION = \
    (cd $(@D)/rtest; \
    if ! test -L rtest.sh ; then \
        $(LN) -fs $(SOURCE_DIR)/rtest/* . ; \
        $(LN) -fs $(SOURCE_DIR)/rtest/graphs/* graphs ; \
        $(LN) -fs $(SOURCE_DIR)/rtest/linux.x86/* linux.x86 ; \
    fi )
COMPONENT_TEST_DIR = $(@D)/rtest
COMPONENT_TEST_ENV = PATH=$(BUILD_DIR_$(BITS)):$(GNUBIN):$(PATH)
 
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += '-n -e "/No. tests: /p"'

# The tests are known to fail consistently because the test samples are out
# of date and not generated with a known configuration.
test: $(TEST_32_and_64)

REQUIRED_PACKAGES += desktop/pdf-viewer/poppler-viewer
REQUIRED_PACKAGES += image/ghostscript
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libwebp
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += print/filter/poppler
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += runtime/python-311
REQUIRED_PACKAGES += runtime/ruby-31
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/libc
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/php-74
REQUIRED_PACKAGES += web/php-80
REQUIRED_PACKAGES += web/php-81
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
