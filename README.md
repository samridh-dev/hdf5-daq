# hdf5-daq
A simple hdf5 c++ library for data acquisition

## Installation
Currently only source installation is possible.
This run script will be sufficient to generate a working executable
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

## Example
```cpp
#include <hdaq.hpp>

constexpr double pi = 3.1415926535898;
constexpr double N = 1e8;
constexpr double M = 16;

int main() {
  
  /// create new HDF5 file
  class hdaq::interface interface("h5file");
  
  /// Create sample dataset
  std::vector<double> data1(N);
  for (int i = 0; i < data1.size(); i++) data1[i] = i * pi / 2;

  /// write data into dataset
  interface.insert_data(data1, "dataset");

  /// create another sample
  std::vector<double> data2(N);
  for (int i = 0; i < data2.size(); i++) data[i] = i * pi / 2;
  
  /// data will be appended to dataset
  interface.insert_data(data2, "dataset");

  /// create some metadata
  std::vector<int>metadata(M);
  for (int i = 0; i < metadata.size(); i++) md[i] = i;

  /// add metadata attribute to prexisting dataset
  /// NOTE: this function will fail in non existing datasets
  interface.insert_attr(metadata, "metadata", "dataset");

  return 0;
}
```

## TODO
Make this fit to integrate with other projects
