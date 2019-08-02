#!bin/sh

pushd $( dirname "$0" )

TEMP_DIR=$PWD/../temp/chaiscript

###########################BULLET3####################################
CHAISCRIPT_DIR_NAME=chaiscript
CHAISCRIPT=$PWD/../external/$CHAISCRIPT_DIR_NAME
CHAISCRIPT_TEMP=$TEMP_DIR/chaiscript_build

###########################Default##################################
INSTALL_DIR=$PWD/../platform/windows/build

############################SETUP###################################
rm -rf $TEMP_DIR

mkdir -p $TEMP_DIR
mkdir -p $CHAISCRIPT_TEMP

pushd $CHAISCRIPT_TEMP
cp -rp $CHAISCRIPT .
pushd $CHAISCRIPT_DIR_NAME

$CMAKE_BIN_PATH/cmake -DBUILD_SAMPLES=OFF -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -G "Unix Makefiles" .
make all install

popd # $CHAISCRIPT_DIR_NAME
popd # $CHAISCRIPT_TEMP

rm -rf $TEMP_DIR

popd
