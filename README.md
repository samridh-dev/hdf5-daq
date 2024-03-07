# hdf5-daq
A simple hdf5 c++ library for data acquisition

## Installation
Currently only source installation is possible.
This run script will be sufficient to generate a working executable
``bash
REPO_NAME="hdf5-daq"
git clone https://github.com/samridh-dev/hdf5-daq.git $REPO_NAME
pushd $REPO_NAME
git submodule update --init --recursive
mkdir -p cmake/build
pushd cmake/build
cmake ../.. -Wdev
make -j $(nproc)
popd
``

## TODO
Make this fit to integrate with other projects
