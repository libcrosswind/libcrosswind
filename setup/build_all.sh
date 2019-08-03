#!bin/sh

pushd $( dirname "$0" )

export CMAKE_BIN_PATH="$(pwd)/./../platform/windows/support/cmake/bin"
export INSTALL_DIR="$(pwd)/./../platform/windows/build"

#sh ./sdl2.sh
#sh ./sdl_image.sh
#sh ./sdl_mixer.sh
sh ./sdl_ttf.sh
#sh ./glew.sh
#sh ./glm.sh
#sh ./bullet.sh
#sh ./chaiscript.sh

read -p "Press Enter to exit"

popd
