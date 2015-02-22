#!bin/sh

pushd $( dirname "$0" )

TEMP_DIR=$PWD/../temp/sdl2

###########################SDL2####################################
SDL2=$PWD/../external/sdl2/SDL-2.0.4-9304
SDL2_TEMP=$TEMP_DIR/sdl2_build


###########################SDL_IMAGE###############################
SDL_IMAGE=$PWD/../external/sdl2/SDL_image-2
SDL_IMAGE_TEMP=$TEMP_DIR/sdlimage_build

###########################Aditional###############################
ZLIB_DIR_NAME=zlib-1.2.8
ZLIB=$SDL_IMAGE/external/$ZLIB_DIR_NAME
ZLIB_TEMP=$TEMP_DIR/zlib_build

JPG=$SDL_IMAGE/external/jpeg-9
JPG_TEMP=$TEMP_DIR/jpg_build

PNG_DIR_NAME=libpng-1.6.2
PNG=$SDL_IMAGE/external/$PNG_DIR_NAME
PNG_TEMP=$TEMP_DIR/phg_build

#TIF=$SDL_IMAGE/external/tiff-4.0.3
#TIF_TEMP=$TEMP_DIR/tiff_build

#WEBP=$SDL_IMAGE/external/libwebp-0.3.0
#WEBP_TEMP=$TEMP_DIR/webp_build


###########################Default##################################
INSTALL_DIR=$PWD/../platform/windows/build

############################SETUP###################################
mkdir -p $TEMP_DIR
mkdir -p $SDL2_TEMP
mkdir -p $SDL_IMAGE_TEMP
mkdir -p $ZLIB_TEMP
mkdir -p $JPG_TEMP
mkdir -p $PNG_TEMP
#mkdir -p $TIF_TEMP
#mkdir -p $WEBP_TEMP

###########################BUILD####################################

pushd $SDL2_TEMP
sh $SDL2/configure --disable-shared --prefix=$INSTALL_DIR 
make clean
make
make install
popd

pushd $ZLIB_TEMP
cp -rp $ZLIB .
pushd $ZLIB_DIR_NAME
make -f win32/Makefile.gcc BINARY_PATH=$INSTALL_DIR/bin INCLUDE_PATH=$INSTALL_DIR/include LIBRARY_PATH=$INSTALL_DIR/lib install
popd
popd



pushd $JPG_TEMP
sh $JPG/configure  --disable-shared --prefix=$INSTALL_DIR 
make clean
make
make install
popd

#pushd $PNG_TEMP
cp -rp $PNG .
pushd $PNG_DIR_NAME
make -f scripts/makefile.msys clean
make -f scripts/makefile.msys prefix="" DESTDIR=$INSTALL_DIR ZLIBINC=$INSTALL_DIR/include ZLIBLIB=$INSTALL_DIR/lib install-static
popd
popd


pushd $SDL_IMAGE_TEMP
sh $SDL_IMAGE/configure   --disable-sdltest --disable-shared --prefix=$INSTALL_DIR LDFLAGS=-L$INSTALL_DIR/lib CPPFLAGS=-I$INSTALL_DIR/include 
make clean
make
make install
popd

popd
