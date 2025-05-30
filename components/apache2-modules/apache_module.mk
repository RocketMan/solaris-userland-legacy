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
# Copyright (c) 2025 Jim Mason <jmason at ibinx doc com>.
#

# Defaults (can be overridden by the including Makefile)
APACHE_MODULE_SRC      ?= mod_example.c
APACHE_MODULE_OBJ      ?= $(patsubst %.c,.libs/%.o,$(APACHE_MODULE_SRC))
APACHE_MODULE_NAME     ?= $(firstword $(APACHE_MODULE_SRC:.c=))
APACHE_MODULE_SO       ?= $(APACHE_MODULE_NAME).so
APACHE_MODULE_LDFLAGS  ?=
APACHE_MODULE_SUBDIR   ?= .

COMPONENT_BUILD_ACTION = \
	cd $(@D)/$(APACHE_MODULE_SUBDIR); \
	$(ENV) $(COMPONENT_BUILD_ENV) \
	$(APXS) -c -o .libs/$(APACHE_MODULE_SO) $(APACHE_MODULE_SRC) && rm -f .libs/$(APACHE_MODULE_SO) ; \
	$(ENV) $(COMPONENT_BUILD_ENV) \
	$(CC) $(CFLAGS) -shared -o .libs/$(APACHE_MODULE_SO) $(APACHE_MODULE_OBJ) $(APACHE_MODULE_LDFLAGS)
