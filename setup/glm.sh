#!bin/sh

pushd $( dirname "$0" )

TEMP_DIR=$PWD/../temp/glm

###########################BULLET3####################################
GLM_DIR_NAME=glm
GLM=$PWD/../external/$GLM_DIR_NAME
GLM_TEMP=$TEMP_DIR/glm_build

###########################Default##################################
INSTALL_DIR=$PWD/../platform/windows/build

############################SETUP###################################
rm -rf $TEMP_DIR

mkdir -p $TEMP_DIR
mkdir -p $GLM_TEMP

pushd $GLM_TEMP
cp -rp $GLM .
pushd $GLM_DIR_NAME


$CMAKE_BIN_PATH/cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -G "Unix Makefiles" .

make all install

popd # $GLM_DIR_NAME
popd # $GLM_TEMP

rm -rf $TEMP_DIR

popd
