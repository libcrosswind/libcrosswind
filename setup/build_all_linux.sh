#!/bin/bash

pushd $( dirname "$0" )

export CMAKE_BIN_PATH="$(pwd)/./../platform/linux/support/cmake/bin"
export INSTALL_DIR="$(pwd)/./../platform/linux/build"

bash ./sdl2_linux.sh

sudo chmod -R 777 "$(pwd)/./../platform/linux/build"

bash ./sdl_image_linux.sh
bash ./sdl_mixer_linux.sh
bash ./sdl_ttf_linux.sh
bash ./glew_linux.sh
bash ./glm_linux.sh
bash ./bullet_linux.sh
#bash ./chaiscript.sh

read -p "Press Enter to exit"

popd
