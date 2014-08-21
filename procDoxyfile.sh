#!/bin/sh
#file: procDoxyfile.sh
# Julien Leider
#
# This script makes appropriate changes to the Doxyfile
# generated by "doxygen -g" to obtain the desired type
# of documentation. It is used by the makefile in "make doc".

echo >> Doxyfile <<EOF

EXTRACT_ALL = YES
INLINE_SOURCE = YES
HAVE_DOT = YES
CALL_GRAPH = YES

EOF