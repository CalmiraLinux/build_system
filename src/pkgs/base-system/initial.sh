#!/bin/bash

echo -e "\e[1m--== WARNING! --==\e[0m"

cat << "EOF"
The installation of this software is straightforward. Although in many cases the
installation instructions could be made shorter and more generic, we have opted
to provide the full instructions for every package to minimize the possibilities
for mistakes. The key to learning what makes a Linux system work is to know what
each package is used for and why you (or the system) may need it.

We do not recommend using optimizations. They can make a program run slightly
faster, but they may also cause compilation difficulties and problems when
running the program. If a package refuses to compile when using optimization,
try to compile it without optimization and see if that fixes the problem. Even
if the package does compile when using optimization, there is the risk it may
have been compiled incorrectly because of the complex interactions between
the code and build tools. Also note that the -march and -mtune options using
values not specified in the book have not been tested. This may cause
problems with the toolchain packages (Binutils, GCC and Glibc). The small
potential gains achieved in using compiler optimizations are often
outweighed by the risks. First-time builders of LFS are encouraged to build
without custom optimizations. The subsequent system will still run very fast
and be stable at the same time.

Before the installation instructions, each installation page provides
information about the package, including a concise description of what it
contains, approximately how long it will take to build, and how much disk space
is required during this building process. Following the installation
instructions, there is a list of programs and libraries (along with brief
descriptions) that the package installs.
EOF

echo -n "Press <ENTER> key to continue..."
read
