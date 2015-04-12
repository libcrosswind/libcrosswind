#!bin/sh

pushd $( dirname "$0" )

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


###########################Default##################################
INSTALL_DIR=$PWD/../platform/windows/build

############################SETUP###################################
rm -rf $TEMP_DIR

mkdir -p $TEMP_DIR
mkdir -p $SDL2_TEMP
mkdir -p $SDL_IMAGE_TEMP
mkdir -p $SDL_TTF_TEMP
mkdir -p $SDL_MIXER_TEMP

mkdir -p $ZLIB_TEMP
mkdir -p $JPG_TEMP
mkdir -p $PNG_TEMP
#mkdir -p $TIF_TEMP
#mkdir -p $WEBP_TEMP

mkdir -p $FREETYPE_TEMP

mkdir -p $OGG_TEMP
mkdir -p $VORBIS_TEMP
#mkdir -p $SMPEG_TEMP


###########################BUILD####################################

pushd $SDL2_TEMP
cp -rp $SDL2 .
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
####################

pushd $ZLIB_TEMP
cp -rp $ZLIB .
pushd $ZLIB_DIR_NAME
make -f win32/Makefile.gcc BINARY_PATH=$INSTALL_DIR/bin INCLUDE_PATH=$INSTALL_DIR/include LIBRARY_PATH=$INSTALL_DIR/lib clean
make -f win32/Makefile.gcc BINARY_PATH=$INSTALL_DIR/bin INCLUDE_PATH=$INSTALL_DIR/include LIBRARY_PATH=$INSTALL_DIR/lib install
popd
popd


pushd $JPG_TEMP
cp -rp $JPG .
pushd $JPG_DIR_NAME
sh ./configure  --disable-shared --prefix=$INSTALL_DIR 
make clean
make
make install
popd
popd

pushd $PNG_TEMP
cp -rp $PNG .
pushd $PNG_DIR_NAME
make -f scripts/makefile.msys clean
make -f scripts/makefile.msys prefix="" DESTDIR=$INSTALL_DIR ZLIBINC=$INSTALL_DIR/include ZLIBLIB=$INSTALL_DIR/lib install-static
popd
popd


pushd $SDL_IMAGE_TEMP
cp -rp $SDL_IMAGE .
pushd $SDL2_IMAGE_DIR_NAME
sh ./configure   --disable-sdltest --disable-shared --prefix=$INSTALL_DIR LDFLAGS=-L$INSTALL_DIR/lib CPPFLAGS=-I$INSTALL_DIR/include 
make clean
make
make install
popd
popd

pushd $FREETYPE_TEMP
cp -rp $FREETYPE .
pushd $FREETYPE_DIR_NAME
sh ./configure  --disable-shared --prefix=$INSTALL_DIR
make clean
make 
make install
popd
popd


pushd $SDL_TTF_TEMP
cp -rp $SDL_TTF .
pushd $SDL_TTF_DIR_NAME
sh ./configure  --disable-sdltest --disable-shared FREETYPE_CONFIG=$INSTALL_DIR/bin/freetype-config --prefix=$INSTALL_DIR LDFLAGS=-L$INSTALL_DIR/lib CPPFLAGS=-I$INSTALL_DIR/include 
make clean
make
make install
popd
popd

pushd $OGG_TEMP
cp -rp $OGG .
pushd $OGG_DIR_NAME
sh ./configure  --disable-shared --prefix=$INSTALL_DIR
make clean
make 
make install
popd
popd

pushd $VORBIS_TEMP
cp -rp $VORBIS .
pushd $VORBIS_DIR_NAME
sh ./configure  --disable-shared --prefix=$INSTALL_DIR
make clean
make 
make install
popd
popd

#Not using smpeg
#pushd $SMPEG_TEMP
#cp -rp $SMPEG .
#pushd $SMPEG_DIR_NAME
#sh ./configure --disable-shared --prefix=$INSTALL_DIR 

#Patching SMPEG dependencies
#sed 's/-luuid/-luuid -lstdc++/g' ./libsmpeg2.la > ./libsmpeg2.la.new 

#rm ./libsmpeg2.la
#mv ./libsmpeg2.la.new ./libsmpeg2.la
####################

#make clean
#make 
#make install
#popd
#popd


pushd $SDL_MIXER_TEMP
cp -rp $SDL_MIXER .
pushd $SDL_MIXER_DIR_NAME
sh ./configure  --disable-sdltest --disable-shared SMPEG_CONFIG=$INSTALL_DIR/bin/smpeg2-config --prefix=$INSTALL_DIR LDFLAGS=-L$INSTALL_DIR/lib CPPFLAGS=-I$INSTALL_DIR/include 
make clean
make 
make install
popd
popd

rm -rf $TEMP_DIR

popd
