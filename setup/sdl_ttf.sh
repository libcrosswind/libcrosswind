#!bin/sh

pushd $( dirname "$0" )

source standard/common.sh .

TEMP_DIR=$PWD/../temp/sdl2

###########################SDL_TTF#################################
SDL_TTF_DIR_NAME=SDL_ttf-2
SDL_TTF=$PWD/../external/sdl2/$SDL_TTF_DIR_NAME
SDL_TTF_TEMP=$TEMP_DIR/sdlttf_build

#########################TTF#######################################
FREETYPE_DIR_NAME=freetype-2.9.1
FREETYPE=$SDL_TTF/external/$FREETYPE_DIR_NAME
FREETYPE_TEMP=$TEMP_DIR/freetype_build

function set_up {
	create_dir $TEMP_DIR
	create_dir $SDL_TTF_TEMP
	create_dir $FREETYPE_TEMP

	copy_to $FREETYPE_TEMP 		$FREETYPE
	copy_to $SDL_TTF_TEMP   	$SDL_TTF
}

function build_sdl_ttf {
	pushd $FREETYPE_TEMP
	pushd $FREETYPE_DIR_NAME
	sh ./configure  --disable-shared --prefix=$INSTALL_DIR
	make clean
	make
	make install
	popd
	popd

	pushd $SDL_TTF_TEMP
	pushd $SDL_TTF_DIR_NAME
	sh ./configure  --disable-sdltest --disable-shared FREETYPE_CONFIG=$INSTALL_DIR/bin/freetype-config --prefix=$INSTALL_DIR LDFLAGS=-L$INSTALL_DIR/lib CPPFLAGS=-I$INSTALL_DIR/include
	make clean
	make
	make install
	popd
	popd
}

###########################BUILD####################################
set_up
build_sdl_ttf
clean_dir $SDL_TTF_TEMP
clean_dir $FREETYPE_TEMP

####################




popd
