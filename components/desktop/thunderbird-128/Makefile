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
# Copyright (c) 2018-2024 Jim Mason <jmason at ibinx doc com>.
#
# Adapted from original code Copyright (c) 2015, 2020, Oracle and/or its
# affiliates. All rights reserved.
#

# parfait is a bit unhappy (22527218)
export PARFAIT_BUILD=no

BUILD_BITS = 64
COMPILER = clang
include ../../../make-rules/shared-macros.mk

ESR = esr

COMPONENT_NAME =	thunderbird
COMPONENT_VERSION =	128.13.0
COMPONENT_PROJECT_URL =	https://www.thunderbird.net/
COMPONENT_ARCHIVE = 	$(COMPONENT_SRC)$(ESR).source.tar.xz
#COMPONENT_ARCHIVE_HASH= \
#    sha256:700ca2e21fef8f76134fc18d901fe890180c21a988ab39ad651554a8ed08a01d
ifndef CANDIDATE_BUILD
MOZILLA_FTP = 		http://ftp.mozilla.org/pub/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)$(ESR)
else
MOZILLA_FTP = 		http://ftp.mozilla.org/pub/$(COMPONENT_NAME)/candidates/$(COMPONENT_VERSION)-candidates/build$(CANDIDATE_BUILD)$(ESR)
endif
COMPONENT_ARCHIVE_URL =	$(MOZILLA_FTP)/source/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB =	tbird/mailer
COMPONENT_ANITYA_ID =	4967

TPNO =			60063

# There are a set of .xpi files (as given in the LANG_LIST definition
# below) that we need. We could download and unpack them individually, but
# they doesn't contain version in its file name and there is lot of them.
# Therefore we will download them and archive them in Userland cache using
# one file with version number.
COMPONENT_ARCHIVE_1 = $(COMPONENT_SRC)$(ESR)-xpi.tar.bz2
#COMPONENT_ARCHIVE_HASH_1 = \
#    sha256:6b55c7ee465adc594532df1b86a163ca3d65d436ab5ee6e997199aedafd17041
COMPONENT_ARCHIVE_URL_1 =       make://download-xpis/$(COMPONENT_ARCHIVE_1)

LANG_LIST = ar ast be bg br ca cak cs cy \
       da de dsb el en-GB en-US es-AR es-ES et \
       eu fi fr fy-NL ga-IE gd gl he hr hsb hu \
       hy-AM id is it ja ka kab kk ko lt ms \
       nb-NO nl nn-NO pl pt-BR pt-PT rm ro ru sk sl \
       sq sr sv-SE tr uk uz vi zh-CN zh-TW

CLEAN_PATHS += $(COMPONENT_DIR)/xpi

# Firefox and Thunderbird share the same firefox*.patch patches. Copy these 
# patches from the Firefox patches directory and the Thunderbird patches to a 
# directory of all files (patches-all).
PATCH_DIR=patches-all
CLEAN_PATHS += $(PATCH_DIR)
COPY_COMMON_FILES_1:= $(shell mkdir -p $(PATCH_DIR))
COPY_COMMON_FILES_2:=  \
    $(shell /usr/bin/rsync -ac patches/* ../firefox-128/patches/* $(PATCH_DIR))

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/common.mk

# Compile with python version in the gate regardless of the mediator
COMPONENT_POST_UNPACK_ACTION += (mkdir bin ; ln -fs $(PYTHON) bin/python3)
CLEAN_PATHS += bin

# /usr/gnu/bin needed to pick up the GNU version of tail and readelf.
# /usr/sbin needed for dtrace.
PATH = $(COMPONENT_DIR)/bin:$(COMPONENT_DIR)/wrapper-node:/usr/gnu/bin:/usr/bin:/usr/sbin

MOZCONFIG = $(SOURCE_DIR)/mozconfig

ifdef DEBUG
# disable code optimization
CFLAGS =
CXXFLAGS =

MOZCONFIG_DEBUG =	$(MOZCONFIG)
MOZCONFIG_NON_DEBUG =	/dev/null
else
MOZCONFIG_DEBUG =	/dev/null
MOZCONFIG_NON_DEBUG =	$(MOZCONFIG)
endif

COMPONENT_PRE_CONFIGURE_ACTION += \
	echo "ac_add_options MOZILLA_OFFICIAL=1" >> $(MOZCONFIG) ; \
	echo "ac_add_options --prefix=/usr" >> $(MOZCONFIG) ; \
	echo "ac_add_options --libdir=/usr/lib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-crashreporter" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-debug-symbols" >> $(MOZCONFIG_NON_DEBUG) ; \
	echo "ac_add_options --disable-install-strip" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --disable-optimize" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --disable-tests" >> $(MOZCONFIG) ; \
	echo "ac_add_options --disable-updater" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-application=comm/mail" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-debug" >> $(MOZCONFIG_DEBUG) ; \
	echo "ac_add_options --enable-jemalloc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-js-shell" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-official-branding" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-optimize" >> $(MOZCONFIG_NON_DEBUG) ; \
	echo "ac_add_options --enable-replace-malloc" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-ffi" >> $(MOZCONFIG) ; \
	echo "ac_add_options --enable-system-pixman" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-intl-api" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-libevent" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-zlib" >> $(MOZCONFIG) ; \
	echo "ac_add_options --with-system-libvpx" >> $(MOZCONFIG) ; \
	echo "ac_add_options --without-wasm-sandboxed-libraries" >> $(MOZCONFIG) ;

CXXFLAGS += -Wno-invalid-offsetof -fpermissive
CXXFLAGS += -stdlib=libc++
LDFLAGS += -lc++

# 28395728
LD_MAP_NOEXBSS.sparc=

# libmozgtk needs to link to gtk3 and others
LD_Z_IGNORE=

# JM 2024-10-03 Firefox in the upstream gate and OI userland
# supply an empty LD_B_DIRECT to disable -Bdirect, ostensibly on
# account of 'missing symbols from gtk3 during Firefox start'.
#
# This does not seem to the case anymore, and probably has not been
# for many years.
#
# Removed the empty LD_B_DIRECT here so -Bdirect is automatically
# appended by the gate.  This allows Firefox to link to its local NSS
# symbols rather than stale ones in the system libucrypt.so, which is
# otherwise a problem in 128esr on 11.3.  More importantly, it helps prevent
# similar issues going forward.
#
# With this change, we can deprecate the erstwhile `solaris11.3-nss.patch`.

# SPARC build seems to require more open files for "Reticulating splines" phase
ENV := ulimit -n 16384; $(ENV)

# UL works better with configure script (instead mach script)
COMPONENT_PRE_CONFIGURE_ACTION += ($(CP) $(SOURCE_DIR)/configure.in $(SOURCE_DIR)/configure);

# make sure that node wrapper is executable
COMPONENT_PRE_CONFIGURE_ACTION += (chmod 555 $(COMPONENT_DIR)/wrapper-node/node);

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/mail/installer ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS))

COMPONENT_POST_INSTALL_ACTION += \
        $(MKDIR) $(PROTOUSRLIBDIR)/thunderbird/distribution/extensions ; $(RM) -rf xpi ; \
        $(TAR) xvf $(COMPONENT_ARCHIVE_1) > /dev/null 2>&1 ; \
        list1='$(LANG_LIST)' ; for f in $$list1 ; do \
            $(CP) xpi/$$f.xpi \
                $(PROTOUSRLIBDIR)/thunderbird/distribution/extensions/langpack-$$f@thunderbird.mozilla.org.xpi ; \
        done ;

MOZ_XPI = $(MOZILLA_FTP)/linux-x86_64/xpi

# Run gmake download-xpis to download a tarball for xpi locally.
download-xpis:
	@echo "download-xpis"
	$(RM) -r $(COMPONENT_DIR)/xpi $(COMPONENT_DIR)/$(COMPONENT_ARCHIVE_1)
	$(MKDIR) $(COMPONENT_DIR)/xpi
	@echo "downloading $(COMPONENT_NAME) xpis"
	list1='$(LANG_LIST)' ; for f in $$list1 ; do \
	    echo $$f; \
	    /usr/bin/curl -R -s -o $(COMPONENT_DIR)/xpi/$$f.xpi \
	        $(MOZ_XPI)/$$f.xpi; \
	    file $(COMPONENT_DIR)/xpi/$$f.xpi | grep ZIP > /dev/null; \
	    if [ $$? -ne 0 ]; then \
	        echo "File $$f is not ZIP archive!"; exit 1; \
	    fi ; \
	done
	(cd $(COMPONENT_DIR); \
	    TZ=UTC gtar cjvf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) --mtime='1970-01-01' --owner=root --group=root xpi/* )
	/usr/bin/sha256sum $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)

license: install
	@echo "regenerating license text"
	unzip -c $(PROTOUSRLIBDIR)/$(COMPONENT_NAME)/omni.ja chrome/messenger/content/messenger/license.html \
	    | lynx  -stdin --dump -nolist > $(COMPONENT_NAME).license

SIGNED_LIST.i386 = libsoftokn3.so libnssdbm3.so libfreebl3.so
SIGNED_LIST.sparc = libsoftokn3.so libnssdbm3.so libfreebl_64fpu_3.so libfreebl_64int_3.so
SIGNED_LIST = $(SIGNED_LIST.$(MACH))

#COMPONENT_POST_INSTALL_ACTION += \
#	slist='$(SIGNED_LIST)' ; for f in $$slist ; do \
#	    mcs -d $(PROTOUSRLIBDIR)/$(COMPONENT_NAME)/$$f ; \
#	    LD_LIBRARY_PATH=$(PROTOUSRLIBDIR)/$(COMPONENT_NAME) $(BUILD_DIR_64)/dist/bin/shlibsign -v -i $(PROTOUSRLIBDIR)/$(COMPONENT_NAME)/$$f ; \
#        done ;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_DIR =    $(@D)/js/src
COMPONENT_TEST_TARGETS=check-jit-test
COMPONENT_TEST_TRANSFORMS = \
	'-e "/^PASSED ALL/,/Failed:/p" ' \
	'-e "/^FAILURES:/,/Failed:/p" ' \
	'-e "/.*/d" '

REQUIRED_PACKAGES += codec/libvpx
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/unzip
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/build/autoconf-213
REQUIRED_PACKAGES += developer/rust/cbindgen
ifneq ($(MACH), sparc)
REQUIRED_PACKAGES += developer/yasm
endif
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/harfbuzz
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-libs
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/zlib
ifneq ($(MACH), sparc)
REQUIRED_PACKAGES += runtime/nodejs
endif
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/llvm/clang-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/browser/lynx
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/toolkit/libxt
