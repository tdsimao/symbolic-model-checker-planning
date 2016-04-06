#!/usr/bin/env bash

# install cudd
cd lib/
wget ftp://vlsi.colorado.edu/pub/cudd-3.0.0.tar.gz
tar xvfz cudd-3.0.0.tar.gz
mkdir cudd
target=$(pwd)/cudd
cd cudd-3.0.0/
    ./configure --prefix=$target --enable-silent-rules  --enable-obj
    make
    make install
cd ../
rm -rf cudd-3.0.0.tar.gz cudd-3.0.0/


#download googletest
git clone https://github.com/google/googletest.git




