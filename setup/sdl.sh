#!bin/sh

pushd $( dirname "$0" )

SDL_DIR=$PWD/../external/SDL-2.0.4-9304
SDL_TEMP_DIR=$PWD/../temp/sdl2/build
SDL_INSTALL_DIR=$PWD/../platform/windows

echo $SDL_DIR
mkdir -p $SDL_TEMP_DIR



pushd $SDL_TEMP_DIR

sh $SDL_DIR/configure --disable-shared --prefix=$SDL_INSTALL_DIR
make
make install

popd




popd
