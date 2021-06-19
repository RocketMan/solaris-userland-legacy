# Solaris Userland Consolidation for 11.3

## Overview
This is a fork of the upstream Userland gate that specifically
targets Solaris 11.3.  It may also be of interest to users of
earlier versions or OpenIndiana.

Note: This fork generally does not contain any packages *not* in the
upstream repo.  For additional software not found in the Userland
consolidation, see my [Solaris Ports
Collection](https://github.com/RocketMan/solaris-ports).

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

## Copyright
Copyright &copy; 2020-2021 Jim Mason.

Copyright (c) 2010, 2021, Oracle and/or its affiliates.

This repository is adapted from material originally authored and published by
Oracle and/or its affiliates at https://github.com/oracle/solaris-userland.

This repository contains files necessary to download, prep, build,
test, package and publish open source software.  It does not include
the source code of the respective open source packages.  This source
code is maintained by its respective developers/communities, and is
downloaded from their sites as part of the build process.

## License
The files in this repository are licensed under the [Common Development and
Distribution License](LICENSE).
