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

BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         ghostscript
COMPONENT_VERSION=	10.01.1
IPS_COMPONENT_VERSION=	$(subst .0,.,$(COMPONENT_VERSION))
COMPONENT_PROJECT_URL=	http://ghostscript.com/
COMPONENT_DOWNLOAD_URL= https://github.com/ArtifexSoftware/ghostpdl-downloads/releases/download
COMPONENT_ARCHIVE_HASH= sha256:4df18a808cd4369f25e02dbcec2f133cb6d674627b2c6b1502020e58d43e32ce
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/gs10011/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1157

$(SOLARIS_11_4_5_ONLY)COMPONENT_NAME_1=	tessdata_best
$(SOLARIS_11_4_5_ONLY)GIT_REPO_1=		https://github.com/tesseract-ocr/$(COMPONENT_NAME_1)
$(SOLARIS_11_4_5_ONLY)GIT_COMMIT_ID_1=	e2aad9b

COMPONENT_BAID=		142601

include $(WS_MAKE_RULES)/common.mk
# some backup files are copied to proto
GPATCH_BACKUP=

PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)

$(SOLARIS_11_3_ONLY)CFLAGS += -D_XPG6

# ghostscript uses a non-standard hybrid-build to build both 32 and 64-bit;
# override these to prevent build failure.
CC_FOR_BUILD=
CONFIGURE_CPPFLAGS=

# force use of shared system libtiff
$(SOLARIS_11_4_5_ONLY)CONFIGURE_OPTIONS +=	--with-system-libtiff
$(SOLARIS_11_3_ONLY)CONFIGURE_OPTIONS +=	--with-libtiff=no

CONFIGURE_OPTIONS +=	--with-drivers=ALL
CONFIGURE_OPTIONS +=	--with-ijs
CONFIGURE_OPTIONS +=	--with-jbig2dec
CONFIGURE_OPTIONS +=	--enable-cups
CONFIGURE_OPTIONS +=	--with-fontpath=/usr/share/fonts
CONFIGURE_OPTIONS +=	--enable-dynamic
CONFIGURE_OPTIONS +=	--disable-compile-inits
CONFIGURE_OPTIONS +=	--without-libidn
$(SOLARIS_11_3_ONLY)CONFIGURE_OPTIONS += --without-tesseract
CONFIGURE_OPTIONS +=	--disable-hidden-visibility

# Sparcv7 cores on test docxwrite
gcc_OPT.sparc.32 = -O0 -munaligned-doubles

# configure options to generate 32 bit binaries
$(BUILD_DIR)/$(MACH32)/.configured: CONFIGURE_OPTIONS += CC="$(CC) -m32"

# configure options to generate 64 bit binaries
$(BUILD_DIR)/$(MACH64)/.configured: CONFIGURE_OPTIONS += CC="$(CC) -m64"

# generate configuration scripts, otherwise libtiff configure fails
COMPONENT_PREP_ACTION = \
	 (cd $(@D); $(RM) -r libpng zlib jpeg tiff openjpeg; autoconf)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_INSTALL_TARGETS += \
	install-exec install-so install-scripts install-data \
	install-contrib-extras

COMPONENT_TEST_RESULTS_DIR =	$(COMPONENT_DIR)/test
COMPONENT_TEST_MASTER =		$(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_CMD =		sh $(COMPONENT_DIR)/test/run
COMPONENT_TEST_ENV +=		TESSDATA_PREFIX="$(SOURCE_DIR_1)"
COMPONENT_TEST_TRANSFORMS +=	"-e '/^Using/d'"
COMPONENT_TEST_TRANSFORMS +=	"-e '/extract.c:.*:extract_subpage_free/d'"

COMPONENT_SYSTEM_TEST_CMD =	sh $(COMPONENT_DIR)/test/run
COMPONENT_SYSTEM_TEST_ENV +=	TESSDATA_PREFIX="$(SOURCE_DIR_1)"
COMPONENT_SYSTEM_TEST_TARGETS =	system-check

REQUIRED_PACKAGES += image/ghostscript
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng14
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg2
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/libc
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxt
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += image/library/libpng
