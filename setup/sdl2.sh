#!bin/sh

pushd $( dirname "$0" )

source standard/common.sh . 

TEMP_DIR=$PWD/../temp/sdl2

###########################SDL2####################################
SDL2_DIR_NAME=SDL-2.0.4-9419
SDL2=$PWD/../external/sdl2/$SDL2_DIR_NAME
SDL2_TEMP=$TEMP_DIR/sdl2_build


###########################SDL_IMAGE###############################
SDL2_IMAGE_DIR_NAME=SDL_image-2
SDL_IMAGE=$PWD/../external/sdl2/$SDL2_IMAGE_DIR_NAME
SDL_IMAGE_TEMP=$TEMP_DIR/sdlimage_build

###########################SDL_TTF#################################
SDL_TTF_DIR_NAME=SDL_ttf-2
SDL_TTF=$PWD/../external/sdl2/$SDL_TTF_DIR_NAME
SDL_TTF_TEMP=$TEMP_DIR/sdlttf_build

###########################SDL_MIXER###############################
SDL_MIXER_DIR_NAME=SDL_mixer-2
SDL_MIXER=$PWD/../external/sdl2/$SDL_MIXER_DIR_NAME
SDL_MIXER_TEMP=$TEMP_DIR/sdlmixer_build


###########################Aditional###############################
#########################IMAGE#######################################
ZLIB_DIR_NAME=zlib-1.2.8
ZLIB=$SDL_IMAGE/external/$ZLIB_DIR_NAME
ZLIB_TEMP=$TEMP_DIR/zlib_build

JPG_DIR_NAME=jpeg-9
JPG=$SDL_IMAGE/external/$JPG_DIR_NAME
JPG_TEMP=$TEMP_DIR/jpg_build

PNG_DIR_NAME=libpng-1.6.2
PNG=$SDL_IMAGE/external/$PNG_DIR_NAME
PNG_TEMP=$TEMP_DIR/phg_build

#TIF=$SDL_IMAGE/external/tiff-4.0.3
#TIF_TEMP=$TEMP_DIR/tiff_build

#WEBP=$SDL_IMAGE/external/libwebp-0.3.0
#WEBP_TEMP=$TEMP_DIR/webp_build

#########################TTF#######################################
FREETYPE_DIR_NAME=freetype-2.5.5
FREETYPE=$SDL_TTF/external/$FREETYPE_DIR_NAME
FREETYPE_TEMP=$TEMP_DIR/freetype_build

#########################MIXER#####################################
OGG_DIR_NAME=libogg-1.3.1
OGG=$SDL_MIXER/external/$OGG_DIR_NAME
OGG_TEMP=$TEMP_DIR/ogg_build

VORBIS_DIR_NAME=libvorbis-1.3.3
VORBIS=$SDL_MIXER/external/$VORBIS_DIR_NAME
VORBIS_TEMP=$TEMP_DIR/vorbis_build

#SMPEG_DIR_NAME=smpeg2-2.0.0
#SMPEG=$SDL_MIXER/external/$SMPEG_DIR_NAME
#SMPEG_TEMP=$TEMP_DIR/smpeg_build

function set_up {
	create_dir $TEMP_DIR
	create_dir $SDL2_TEMP
	create_dir $SDL_IMAGE_TEMP
	create_dir $SDL_TTF_TEMP
	create_dir $SDL_MIXER_TEMP
	create_dir $ZLIB_TEMP
	create_dir $JPG_TEMP
	create_dir $PNG_TEMP
	#create_dir $TIF_TEMP
	#create_dir $WEBP_TEMP
	create_dir $FREETYPE_TEMP
	create_dir $OGG_TEMP
	create_dir $VORBIS_TEMP

	copy_to $SDL2_TEMP 			$SDL2
	copy_to $ZLIB_TEMP 			$ZLIB
	copy_to $JPG_TEMP 			$JPG
	copy_to $PNG_TEMP 			$PNG
	copy_to $SDL_IMAGE_TEMP 	$SDL_IMAGE
	copy_to $FREETYPE_TEMP 		$FREETYPE
	copy_to $SDL_TTF_TEMP   	$SDL_TTF
	copy_to $OGG_TEMP   		$OGG
	copy_to $VORBIS_TEMP   		$VORBIS
	copy_to $SDL_MIXER_TEMP		$SDL_MIXER

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

function build_sdl_image {
	pushd $ZLIB_TEMP
	pushd $ZLIB_DIR_NAME
	make -f win32/Makefile.gcc BINARY_PATH=$INSTALL_DIR/bin INCLUDE_PATH=$INSTALL_DIR/include LIBRARY_PATH=$INSTALL_DIR/lib clean
	make -f win32/Makefile.gcc BINARY_PATH=$INSTALL_DIR/bin INCLUDE_PATH=$INSTALL_DIR/include LIBRARY_PATH=$INSTALL_DIR/lib install
	popd
	popd

	pushd $JPG_TEMP
	pushd $JPG_DIR_NAME
	sh ./configure  --disable-shared --prefix=$INSTALL_DIR 
	make clean
	make
	make install
	popd
	popd

	pushd $PNG_TEMP
	pushd $PNG_DIR_NAME
	make -f scripts/makefile.msys clean
	make -f scripts/makefile.msys prefix="" DESTDIR=$INSTALL_DIR ZLIBINC=$INSTALL_DIR/include ZLIBLIB=$INSTALL_DIR/lib install-static
	popd
	popd
	
	pushd $SDL_IMAGE_TEMP
	pushd $SDL2_IMAGE_DIR_NAME
	sh ./configure  --disable-sdltest --disable-shared --prefix=$INSTALL_DIR LDFLAGS=-L$INSTALL_DIR/lib CPPFLAGS=-I$INSTALL_DIR/include 
	make clean
	make
	make install
	popd
	popd
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
clean_dir $TEMP_DIR
set_up
build_sdl
build_sdl_image
build_sdl_ttf
build_sdl_mixer
clean_dir $TEMP_DIR
####################
 



popd
