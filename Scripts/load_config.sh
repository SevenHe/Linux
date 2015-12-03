#!/bin/bash
# load them in to .bashrc
TEST="test for config"
export $TEST
TESTONE=$TEST
echo $TESTONE
exit
CPPFLAGS='-I/opt/gtk/include'
LDFLAGS='-L/opt/gtk/lib'
PKG_CONFIG_PATH='/opt/gtk/lib/pkgconfig'
export CPPFLAGS LDFLAGS PKG_CONFIG_PATH
LD_LIBRARY_PATH="/opt/gtk/lib"
PATH="/opt/gtk/bin:$PATH"
export LD_LIBRARY_PATH PATH
