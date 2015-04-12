#!bin/sh

pushd $( dirname "$0" )

sh ./sdl2.sh
read -p "SDL OK"
sh ./glew.sh 
read -p "Glew OK"
sh ./glm.sh
sh ./bullet.sh
sh ./chaiscript.sh

popd