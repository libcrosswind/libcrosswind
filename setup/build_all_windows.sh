#!bin/sh

pushd $( dirname "$0" )

export CMAKE_BIN_PATH="$(pwd)/./../platform/windows/support/cmake/bin"
export INSTALL_DIR="$(pwd)/./../platform/windows/build"

sh ./sdl2_windows.sh
sh ./sdl_image_windows.sh
sh ./sdl_mixer_windows.sh
sh ./sdl_ttf_windows.sh
sh ./glew_windows.sh
sh ./glm_windows.sh
sh ./bullet_windows.sh
#sh ./chaiscript_windows.sh

read -p "Press Enter to exit"

popd
