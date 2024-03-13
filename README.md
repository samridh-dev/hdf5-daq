# hdf5-daq
A simple hdf5 c++ library for data acquisition

## Installation
Currently only source installation is possible.
This run script will be sufficient to generate a working executable. Edit as
you see fit.

NOTE: to configure the project, refer to the /cmake/config.cmake file.

```bash
REPO_NAME="hdf5-daq"
git clone https://github.com/samridh-dev/hdf5-daq.git $REPO_NAME
pushd $REPO_NAME
git submodule update --init --recursive
mkdir -p bin/ dat/
mkdir -p cmake/build/
pushd cmake/build
cmake ../.. -Wdev
make -j $(nproc)
popd
```

## Usage
See example

### Cmake usage
If hdf5daq is provided as a submodule, simply add this command to your
CMakeLists.txt
```cmake
add_subdirectory(/path/to/hdf5daq-submodule)
```

If installed globally, then this command can also be used.
```cmake
find_package(hdf5daq-module)
```

## Example
```cpp
#include <hdaq.hpp>

const double pi = 3.1415926535898;
const double N = 1e4;
const double M = 16;

int main() {
  
  /// create new HDF5 file
  class hdaq::interface interface("h5file");
  
  /// Create sample dataset
  class hdaq::dataset<double> data1(N);
  for (int i = 0; i < data1.size(); i++) data1[i] = i * pi / 2;

  /// write data into dataset
  interface.insert(data1, "dataset");

  /// create another sample
  class hdaq::dataset<double> data2(N);
  for (int i = 0; i < data2.size(); i++) data2[i] = pi / (2 * i);
  
  /// data will be appended to the same dataset
  interface.insert(data2, "dataset");

  /// create some attributes for our datataset
  hdaq::attribute<int> metadata("metadata",M);
  for (int i = 0; i < metadata.size(); i++) metadata[i] = i;

  /// add metadata attribute to prexisting dataset
  /// NOTE: this function will fail in non existing datasets
  interface.insert(metadata, "dataset");

  return 0;
}
```
