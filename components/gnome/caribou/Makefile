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
# Copyright (c) 2015, 2023, Oracle and/or its affiliates.
#

BUILD_BITS=  		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		caribou
COMPONENT_VERSION=	0.4.21
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Caribou
COMPONENT_ARCHIVE_HASH= \
	sha256:9c43d9f4bd30f4fea7f780d4e8b14f7589107c52e9cb6bd202bd0d1c2064de55
COMPONENT_BUGDB=	gnome/accessibility
COMPONENT_ANITYA_ID=	253

COMPONENT_BAID=		38921

TEST_TARGET = $(NO_TESTS)

PYTHON_VERSION = 3.11

include $(WS_MAKE_RULES)/gnome-component.mk

# Use explicit Python version rather than the default one
CONFIGURE_ENV +=	PYTHON=$(PYTHON)

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

CONFIGURE_OPTIONS += --disable-docs
CONFIGURE_OPTIONS += --disable-static
# Normally we should prefer gtk3 over gtk2, but just in case there are any
# gtk2-based applications, this will improve accessibility for them.
CONFIGURE_OPTIONS += --enable-gtk2-module
CONFIGURE_OPTIONS += --enable-gtk3-module
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)

PKG_MACROS += PYVER="$(PYTHON_VERSION)"

REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/at-spi2-atk
REQUIRED_PACKAGES += library/desktop/at-spi2-core
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgee
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/python/pygobject-3-311
REQUIRED_PACKAGES += runtime/python-311
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxtst
