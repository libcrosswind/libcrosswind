#!bin/sh

pushd $( dirname "$0" )

TEMP_DIR=$PWD/../temp/glew_cmake

###########################BULLET3####################################
GLEW_CMAKE_DIR_NAME=glew_cmake
GLEW_CMAKE=$PWD/../external/$GLEW_CMAKE_DIR_NAME
GLEW_CMAKE_TEMP=$TEMP_DIR/glew_cmake_build

###########################Default##################################
INSTALL_DIR=$PWD/../platform/windows/build

############################SETUP###################################
rm -rf $TEMP_DIR

mkdir -p $TEMP_DIR
mkdir -p $GLEW_CMAKE_TEMP

pushd $GLEW_CMAKE_TEMP
cp -rp $GLEW_CMAKE .
pushd $GLEW_CMAKE_DIR_NAME

mkdir -p build

pushd build

cmake -Dglew-cmake_BUILD_SHARED=OFF -DONLY_LIBS=ON -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -G "Unix Makefiles" ..

make all install

popd # build

popd # $GLEW_CMAKE_DIR_NAME
popd # $GLEW_CMAKE_TEMP

rm -rf $TEMP_DIR

popd