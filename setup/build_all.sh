#!bin/sh

pushd $( dirname "$0" )

sh ./sdl2.sh
sh ./glew.sh 
sh ./glm.sh
sh ./bullet.sh
sh ./chaiscript.sh

popd