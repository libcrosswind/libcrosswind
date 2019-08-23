#!bin/sh

pushd $( dirname "$0" )

source standard/common_windows.sh .

TEMP_DIR=$PWD/../temp/glm

###########################BULLET3####################################
GLM_DIR_NAME=glm
GLM=$PWD/../external/$GLM_DIR_NAME
GLM_TEMP=$TEMP_DIR/glm_build

###########################Default##################################
INSTALL_DIR=$PWD/../platform/windows/build

############################SETUP###################################
rm -rf $GLM_TEMP

mkdir -p $TEMP_DIR
mkdir -p $GLM_TEMP

pushd $GLM_TEMP
cp -rp $GLM .
pushd $GLM_DIR_NAME


$CMAKE_BIN_PATH/cmake -DGLM_TEST_ENABLE=OFF -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -G "Unix Makefiles" .

make all install

popd # $GLM_DIR_NAME
popd # $GLM_TEMP

rm -rf $GLM_TEMP

popd
