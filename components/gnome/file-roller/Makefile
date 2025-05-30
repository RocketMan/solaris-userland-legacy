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
# Copyright (c) 2016, 2021, Oracle and/or its affiliates.
#

BUILD_BITS=		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		file-roller
COMPONENT_VERSION=	3.38.1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/FileRoller
COMPONENT_ARCHIVE_HASH= \
	sha256:94a0130e12d321aa119793a14d09716523e2e4a61f29570cee53fd88dd6abc57
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	5392

COMPONENT_BAID=		101178
BUILD_STYLE=		meson

TEST_TARGET = $(NO_TESTS)

$(SOLARIS_11_3_ONLY)CFLAGS += -DSOLARIS_11_3

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += -Dpackagekit=false
CONFIGURE_OPTIONS += -Dlibarchive=false
$(SOLARIS_11_3_ONLY)CONFIGURE_OPTIONS += -Dnautilus-actions=false

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_INSTALL_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --libexecdir="$(USRLIB)"

COMPONENT_POST_INSTALL_ACTION.64 += \
        $(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/file-roller.1 \
                $(PROTO_DIR)/usr/share/man/man1/file-roller.1;

MANIFEST_COMPARE=/usr/bin/true

REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += system/library/math
