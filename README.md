# Solaris Userland Consolidation for 11.3

## Overview
This is a fork of the upstream Userland gate that specifically
targets Solaris 11.3.  It may also be of interest to users of
earlier versions or OpenIndiana.

The goal of this repo is to build the latest userland software on 11.3
without breaking any existing dependencies (e.g., GNOME 2, gnutls)

I have not built every package in this repo; if you find something
which does not build on 11.3 and want to submit a PR, I encourage you
to do that.

Some packages that I have successfully built on 11.3 are gtk3, evince,
rust, firefox, and thunderbird.

Note: This fork generally does not contain any packages *not* in the
upstream repo, such as the Nimbus gtk3 theme and epiphany.  For
additional software not found in the Userland consolidation, see my
[Solaris Ports Collection](https://github.com/RocketMan/solaris-ports).

## Getting Started
This README provides a very brief overview of the gate (i.e., source
code repository), how to retrieve a copy, and how to build it.

## Getting the Bits

    $ git clone https://github.com/RocketMan/solaris-userland-legacy

### Component build
Build individual components using following:

Setup the workspace for building components

    $ cd (your-workspace)/components ; gmake setup

Build the individual component

    $ cd (component-dir) ; gmake publish

# Copyright
Copyright &copy; 2020 Jim Mason.  All rights reserved.

This repository is adapted from code Copyright (c) 2010, 2019, Oracle and/or its affiliates. All rights reserved.
