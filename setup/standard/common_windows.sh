#!bin/bash

#Installation directory
INSTALL_DIR=$PWD/../platform/windows/build

#Functions

function create_dir {
	mkdir -p $1
}

function copy_to {

pushd $1
	cp -rp $2 .
popd

}

function clean_dir {
	rm -rf $1
}
