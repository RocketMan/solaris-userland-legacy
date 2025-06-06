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

BUILD_BITS=		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		grilo-plugins
COMPONENT_VERSION=	0.3.15
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Grilo
COMPONENT_ARCHIVE_HASH= \
	sha256:8518c3d954f93095d955624a044ce16a7345532f811d299dbfa1e114cfebab33
COMPONENT_BUGDB=	gnome/multimedia
COMPONENT_ANITYA_ID=	10929

COMPONENT_BAID=		130756
BUILD_STYLE=		meson

include $(WS_MAKE_RULES)/gnome-component.mk

# For various non-standard #include extensions.
CFLAGS += -D__EXTENSIONS__
$(SOLARIS_11_3_ONLY)LDFLAGS += -lsocket -lnls

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(GNUBIN):$(PATH)

CONFIGURE_OPTIONS += -Denable-lua-factory=no
CONFIGURE_OPTIONS += -Denable-dmap=no
$(SOLARIS_11_3_ONLY)CONFIGURE_OPTIONS += -Denable-bookmarks=yes
$(SOLARIS_11_3_ONLY)CONFIGURE_OPTIONS += -Denable-raitv=no

# Temporary workaround until all build machines are running meson-0.63
COMPONENT_POST_INSTALL_ACTION += \
for f in $(PROTO_DIR)/usr/share/help/[a-z]*/examples ; do \
    (cd $$f ; $(RM) example-tmdb.c ; \
	$(SYMLINK) ../../C/grilo-plugins/../examples/example-tmdb.c . ); \
done ;

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/desktop/librest
REQUIRED_PACKAGES += library/desktop/search/tracker
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmime
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/desktop/gom
REQUIRED_PACKAGES += library/desktop/grilo
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/gnome/libmediaart
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/liboauth
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += system/network/avahi/gui
