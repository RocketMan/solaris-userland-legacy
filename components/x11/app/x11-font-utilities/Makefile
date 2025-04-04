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
# Copyright (c) 2018, 2023, Oracle and/or its affiliates.
#

BUILD_BITS =            64
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mkfontscale
COMPONENT_VERSION=	1.2.2
COMPONENT_ARCHIVE_HASH= \
	sha256:8ae3fb5b1fe7436e1f565060acaa3e2918fe745b0e4979b5593968914fe2d5c4
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_BUGDB=        x11/xclients
COMPONENT_ANITYA_ID=	15043
COMPONENT_BAID=		122777

COMPONENT_NAME_2=       bdftopcf
COMPONENT_VERSION_2=    1.1.1
COMPONENT_ARCHIVE_URL_2=$(COMPONENT_PROJECT_URL)/releases/individual/util/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2=       \
    sha256:11c953d53c0f3ed349d0198dfb0a40000b5121df7eef09f2615a262892fed908
COMPONENT_ANITYA_ID_2=	15054
COMPONENT_BAID_2=	140608

COMPONENT_NAME_3=       font-util
COMPONENT_VERSION_3=    1.4.0
COMPONENT_ARCHIVE_HASH_3=       \
    sha256:9f724bf940128c7e39f7252bd961cd38cfac2359de2100a8bed696bf40d40f7d
COMPONENT_ARCHIVE_URL_3= \
    $(COMPONENT_PROJECT_URL)/releases/individual/font/$(COMPONENT_ARCHIVE_3)
COMPONENT_ANITYA_ID_3=	15055
COMPONENT_BAID_3=	139251

TEST_TARGET = $(NO_TESTS)

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

LIST = 2 3

define extra-target-rules
$(BUILD_DIR)/%_$(1)/.configured: SOURCE_DIR=$$(SOURCE_DIR_$(1))
endef

$(foreach n, $(LIST), \
    $(eval COMPONENT_SRC_$(n) = $(COMPONENT_NAME_$(n))-$(COMPONENT_VERSION_$(n))) \
    $(eval COMPONENT_ARCHIVE_$(n) ?= $(COMPONENT_SRC_$(n)).tar.xz) \
    $(eval COMPONENT_ARCHIVE_URL_$(n) ?= $$(COMPONENT_ARCHIVE_URL:$$(COMPONENT_ARCHIVE)=$(COMPONENT_ARCHIVE_$(n)))) \
    $(eval BUILD_DIR_$(n) += $(BUILD_DIR_$(MK_BITS))_$(n)) \
    $(eval CONFIGURE_$(MK_BITS) += $(BUILD_DIR_$(n))/.configured) \
    $(eval BUILD_$(MK_BITS)_$(n) += $(BUILD_DIR_$(n))/.built) \
    $(eval BUILD_TARGET += $(BUILD_$(MK_BITS)_$(n))) \
    $(eval INSTALL_$(MK_BITS)_$(n) += $(BUILD_DIR_$(n))/.installed) \
    $(eval INSTALL_TARGET += $(INSTALL_$(MK_BITS)_$(n))) \
    $(eval $(call extra-target-rules,$(n))) \
)

include $(WS_MAKE_RULES)/x11-component.mk

# Extra configure flag just for mkfontscale
$(BUILD_DIR_$(MK_BITS))/.configured:	CONFIGURE_OPTIONS += --with-bzip2

COMPONENT_INSTALL_ARGS += pkgconfigdir="$(DESTDIR)/usr/share/pkgconfig"

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += x11/library/libfontenc
