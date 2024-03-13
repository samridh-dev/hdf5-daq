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
