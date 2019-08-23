#!/bin/bash

pushd $( dirname "$0" )

source standard/common_linux.sh .

TEMP_DIR=$PWD/../temp/bullet3

###########################BULLET3####################################
BULLET3_DIR_NAME=bullet3
BULLET3=$PWD/../external/$BULLET3_DIR_NAME
BULLET3_TEMP=$TEMP_DIR/bullet3_build

###########################Default##################################
INSTALL_DIR=$PWD/../platform/linux/build

############################SETUP###################################
rm -rf $BULLET3_TEMP

mkdir -p $TEMP_DIR
mkdir -p $BULLET3_TEMP

pushd $BULLET3_TEMP
cp -rp $BULLET3 .
pushd $BULLET3_DIR_NAME
mkdir -p build

pushd build

sudo chmod -R 777 "$(pwd)"

CXXFLAGS="-fpermissive"
$CMAKE_BIN_PATH/cmake -DUSE_GLUT=OFF -DBUILD_OPENGL3_DEMOS=OFF -DBUILD_CPU_DEMOS=OFF -DBUILD_BULLET2_DEMOS=OFF -DBUILD_EXTRAS=OFF -DBUILD_UNIT_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -G "Unix Makefiles" ..

make all install

popd #build

popd #$BULLET3_DIR_NAME
popd #$BULLET3_TEMP

rm -rf $BULLET3_TEMP

popd
