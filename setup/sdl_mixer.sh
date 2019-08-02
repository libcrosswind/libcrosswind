#!bin/sh

pushd $( dirname "$0" )

source standard/common.sh .

TEMP_DIR=$PWD/../temp/sdl2

###########################SDL_MIXER###############################
SDL_MIXER_DIR_NAME=SDL_mixer-2
SDL_MIXER=$PWD/../external/sdl2/$SDL_MIXER_DIR_NAME
SDL_MIXER_TEMP=$TEMP_DIR/sdlmixer_build

#########################MIXER#####################################
OGG_DIR_NAME=libogg-1.3.2
OGG=$SDL_MIXER/external/$OGG_DIR_NAME
OGG_TEMP=$TEMP_DIR/ogg_build

VORBIS_DIR_NAME=libvorbis-1.3.5
VORBIS=$SDL_MIXER/external/$VORBIS_DIR_NAME
VORBIS_TEMP=$TEMP_DIR/vorbis_build

#SMPEG_DIR_NAME=smpeg2-2.0.0
#SMPEG=$SDL_MIXER/external/$SMPEG_DIR_NAME
#SMPEG_TEMP=$TEMP_DIR/smpeg_build

function set_up {
	create_dir $TEMP_DIR
	create_dir $SDL_MIXER_TEMP
	create_dir $OGG_TEMP
	create_dir $VORBIS_TEMP

	copy_to $OGG_TEMP   		$OGG
	copy_to $VORBIS_TEMP   		$VORBIS
	copy_to $SDL_MIXER_TEMP		$SDL_MIXER

}

function build_sdl_mixer {
	pushd $OGG_TEMP
	pushd $OGG_DIR_NAME
	sh ./configure  --disable-shared --prefix=$INSTALL_DIR
	make clean
	make
	make install
	popd
	popd

	pushd $VORBIS_TEMP
	pushd $VORBIS_DIR_NAME
	sh ./configure  --disable-shared --prefix=$INSTALL_DIR
	make clean
	make
	make install
	popd
	popd


	pushd $SDL_MIXER_TEMP
	pushd $SDL_MIXER_DIR_NAME
	sh ./configure  --disable-sdltest --disable-shared SMPEG_CONFIG=$INSTALL_DIR/bin/smpeg2-config --prefix=$INSTALL_DIR LDFLAGS=-L$INSTALL_DIR/lib CPPFLAGS=-I$INSTALL_DIR/include
	make clean
	make
	make install
	popd
	popd
}

###########################BUILD####################################
set_up
build_sdl_mixer
clean_dir $SDL_MIXER_TEMP
clean_dir $OGG_TEMP
clean_dir $VORBIS_TEMP

####################

popd
