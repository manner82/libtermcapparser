libtermcapparser
================

This repository contains a terminal emulator library originating from putty SSH client.

Build
-----

# To build and install the library for linux:
make linux PREFIX=<path>

# To build and install the library for win32:
export XPATH=<the path containing the cross toolchain>
export XTYPE=<the type of the crosscompiler>  # eg. in case of "i686-w64-mingw32.shared", the c compiler i686-w64-mingw32.shared-gcc will be used
make win32 PREFIX=<path>

# clean, distclean, install, install-strip, uninstall... subtargets:
make <os>-<subtarget>
# For example for the "install" subtarget for "linux" build you would:
make linux-clean
# Note: For all these commands to work, you need to run the "dep" subtarget first!
# Note: Clean before changing os!

# Tests check the installed version, so you'll need to specify the PREFIX:
make linux-check PREFIX=/tmp
