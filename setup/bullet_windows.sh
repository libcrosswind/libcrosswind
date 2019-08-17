#!bin/sh

pushd $( dirname "$0" )

source standard/common_windows.sh .

TEMP_DIR=$PWD/../temp/bullet3

###########################BULLET3####################################
BULLET3_DIR_NAME=bullet3
BULLET3=$PWD/../external/$BULLET3_DIR_NAME
BULLET3_TEMP=$TEMP_DIR/bullet3_build

###########################Default##################################
INSTALL_DIR=$PWD/../platform/windows/build

############################SETUP###################################
rm -rf $BULLET3_TEMP

mkdir -p $TEMP_DIR
mkdir -p $BULLET3_TEMP

pushd $BULLET3_TEMP
cp -rp $BULLET3 .
pushd $BULLET3_DIR_NAME
mkdir -p build

pushd build

CXXFLAGS="-fpermissive"
$CMAKE_BIN_PATH/cmake -DUSE_GLUT=OFF -DBUILD_OPENGL3_DEMOS=OFF -DBUILD_CPU_DEMOS=OFF -DBUILD_BULLET2_DEMOS=OFF -DBUILD_EXTRAS=OFF -DBUILD_UNIT_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -G "Unix Makefiles" ..

make all install

popd #build

popd #$BULLET3_DIR_NAME
popd #$BULLET3_TEMP

rm -rf $BULLET3_TEMP

popd
