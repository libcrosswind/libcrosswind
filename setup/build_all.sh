#!bin/sh

pushd $( dirname "$0" )

PATH=$PATH:$( dirname "$0" )/../platform/windows/support/cmake/bin
export PATH

sh ./sdl2.sh
sh ./glew.sh 
sh ./glm.sh
sh ./bullet.sh
sh ./chaiscript.sh

popd