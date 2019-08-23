#!/bin/bash

pushd $( dirname "$0" )

source standard/common_linux.sh .

TEMP_DIR=$PWD/../temp/sdl2

###########################SDL_IMAGE###############################
SDL2_IMAGE_DIR_NAME=SDL_image-2
SDL_IMAGE=$PWD/../external/sdl2/$SDL2_IMAGE_DIR_NAME
SDL_IMAGE_TEMP=$TEMP_DIR/sdlimage_build

###########################Aditional###############################
#########################IMAGE#######################################
ZLIB_DIR_NAME=zlib-1.2.11
ZLIB=$SDL_IMAGE/external/$ZLIB_DIR_NAME
ZLIB_TEMP=$TEMP_DIR/zlib_build

JPG_DIR_NAME=jpeg-9b
JPG=$SDL_IMAGE/external/$JPG_DIR_NAME
JPG_TEMP=$TEMP_DIR/jpg_build

PNG_DIR_NAME=libpng-1.6.37
PNG=$SDL_IMAGE/external/$PNG_DIR_NAME
PNG_TEMP=$TEMP_DIR/phg_build


function set_up {
	create_dir $TEMP_DIR
	create_dir $SDL_IMAGE_TEMP
	create_dir $ZLIB_TEMP
	create_dir $JPG_TEMP
	create_dir $PNG_TEMP

	copy_to $ZLIB_TEMP 			$ZLIB
  copy_to $JPG_TEMP 			$JPG
	copy_to $PNG_TEMP 			$PNG
	copy_to $SDL_IMAGE_TEMP 	$SDL_IMAGE
}

function build_sdl_image {
	pushd $ZLIB_TEMP
	pushd $ZLIB_DIR_NAME
	sudo chmod -R 777 "$(pwd)"
  make -f win32/Makefile.gcc BINARY_PATH=$INSTALL_DIR/bin INCLUDE_PATH=$INSTALL_DIR/include LIBRARY_PATH=$INSTALL_DIR/lib clean
	make -f win32/Makefile.gcc BINARY_PATH=$INSTALL_DIR/bin INCLUDE_PATH=$INSTALL_DIR/include LIBRARY_PATH=$INSTALL_DIR/lib install
	popd
	popd

	pushd $PNG_TEMP
	pushd $PNG_DIR_NAME
#	./configure --prefix=$INSTALL_DIR/ --with-zlib-prefix=$INSTALL_DIR/
#	make
#	make install
	sudo chmod -R 777 "$(pwd)"
	make -f scripts/makefile.msys clean
	make -f scripts/makefile.gcc prefix=$INSTALL_DIR DESTDIR=$INSTALL_DIR ZLIBINC=$INSTALL_DIR/include ZLIBLIB=$INSTALL_DIR/lib static
	make -f scripts/makefile.msys prefix="" DESTDIR=$INSTALL_DIR ZLIBINC=$INSTALL_DIR/include ZLIBLIB=$INSTALL_DIR/lib install-static
	popd
	popd

	pushd $JPG_TEMP
	pushd $JPG_DIR_NAME
	sudo chmod -R 777 "$(pwd)"
	sh ./configure  --disable-shared --prefix=$INSTALL_DIR
	make clean
	make
	make install
	popd
	popd

	pushd $SDL_IMAGE_TEMP
	pushd $SDL2_IMAGE_DIR_NAME
	sudo chmod -R 777 "$(pwd)"
	sh ./configure  --disable-sdltest --disable-shared --prefix=$INSTALL_DIR SDL2_CONFIG=$INSTALL_DIR/bin/sdl2-config LDFLAGS=-L$INSTALL_DIR/lib CPPFLAGS=-I$INSTALL_DIR/include
	make clean
	make
	make install
	popd
	popd
}

###########################BUILD####################################
clean_dir $SDL_IMAGE_TEMP
clean_dir $ZLIB_TEMP
clean_dir $JPG_TEMP
clean_dir $PNG_TEMP

set_up
build_sdl_image

clean_dir $SDL_IMAGE_TEMP
clean_dir $ZLIB_TEMP
clean_dir $JPG_TEMP
clean_dir $PNG_TEMP

####################

popd
