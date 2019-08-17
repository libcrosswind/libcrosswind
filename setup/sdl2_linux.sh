#!/bin/bash

pushd $( dirname "$0" )

source standard/common_linux.sh .

TEMP_DIR=$PWD/../temp/sdl2

###########################SDL2####################################
SDL2_DIR_NAME=SDL2-2
SDL2=$PWD/../external/sdl2/$SDL2_DIR_NAME
SDL2_TEMP=$TEMP_DIR/sdl2_build

function set_up {
	create_dir $TEMP_DIR
	create_dir $SDL2_TEMP

	copy_to $SDL2_TEMP 			$SDL2
}


function build_sdl {

	pushd $SDL2_TEMP
	pushd $SDL2_DIR_NAME
	sh ./configure --disable-shared --prefix=$INSTALL_DIR
	make clean
	make
	make install
	popd
	popd

	#Removing -XCClinker
	sed 's/-XCClinker//g' $INSTALL_DIR/bin/sdl2-config > $INSTALL_DIR/bin/sdl2-config.new

	rm $INSTALL_DIR/bin/sdl2-config
	mv $INSTALL_DIR/bin/sdl2-config.new $INSTALL_DIR/bin/sdl2-config

}


###########################BUILD####################################
clean_dir $SDL2_TEMP

set_up
build_sdl

clean_dir $SDL2_TEMP
####################




popd
