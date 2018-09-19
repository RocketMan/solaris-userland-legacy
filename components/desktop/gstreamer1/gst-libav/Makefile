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
# Copyright (c) 2015, 2018, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            32_and_64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-libav
COMPONENT_VERSION=	1.10.3
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:9a6bc165b1862b18b98d9f1755c43806e4839a80f69ec7ea9a2dab61b65752a9
COMPONENT_ARCHIVE_URL=	https://gstreamer.freedesktop.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
#COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	gnome/multimedia
COMPONENT_ANITYA_ID=	1263

TPNO=			33710

# Hook up tests after build servers are installed with dependencies
TEST_TARGET= $(SKIP_TEST)

# Only build for 2.7 for now as we need 32-bit and 64-bit support; all of the
# GNOME and desktop components must be built for Python 2.7 for now.
PYTHON_VERSIONS= 2.7

PATH=/usr/gnu/bin:/usr/bin

include $(WS_MAKE_RULES)/common.mk

# Use the build area of gstreamer and gst-plugins-base
GST_BASE = $(WS_COMPONENTS)/desktop/gstreamer1/gstreamer/build/prototype/$(MACH)
GST_PL_BASE = $(WS_COMPONENTS)/desktop/gstreamer1/gst-plugins-base/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(GST_BASE)$(USRLIB)/pkgconfig:$(GST_PL_BASE)$(USRLIB)/pkgconfig
 
CPPFLAGS += -I$(GST_BASE)/usr/include/gstreamer-1.0 -I$(GST_PL_BASE)/usr/include/gstreamer-1.0/
LD_OPTIONS += -L $(GST_BASE)$(USRLIB) -L $(GST_PL_BASE)$(USRLIB)

CXXFLAGS += -std=c++11
LDFLAGS += -m$(BITS)
COMPONENT_BUILD_ENV += V=1

# configure script uses AC_CHECK_PROG erroneously; AC_CHECK_PROG looks for a
# program in $PATH by default, and fails even if you provide an absolute path
# to the command (no idea why); override the failed check.
CONFIGURE_ENV += ac_cv_prog_HAVE_CXX=yes


# Ensure system-default python is not used.
CONFIGURE_ENV += PYTHON="$(PYTHON.2.7)"

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

CONFIGURE_OPTIONS += --with-system-libav

# Required due to patches.
COMPONENT_PREP_ACTION += ( cd $(@D) ; NOCONFIGURE=1 $(CONFIG_SHELL) autogen.sh );

REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += media/ffmpeg
