hdaq::interface::interface(const std::string& filename) :
  file(get_h5fname(filename), H5F_ACC_TRUNC) 
{}

template <typename T>
void 
hdaq::interface::insert(const std::vector<T>& vec, const std::string& name) {
  try {
    H5::Exception::dontPrint();
    std::vector<hsize_t>dims{vec.size()};
    H5::DataSpace dspace(dims.size(), dims.data());
    H5::DataSet dset = file.createDataSet(name, get_h5predtype<T>(), dspace);
    dset.write(vec.data(), get_h5predtype<T>());
  } catch (H5::FileIException error) {
    error.printErrorStack();
  } catch (H5::DataSetIException error) {
    error.printErrorStack();
  } catch (H5::DataSpaceIException error) {
    error.printErrorStack();
  }
}

template <typename T>
constexpr H5::PredType 
hdaq::interface::get_h5predtype() {
  if (std::is_same<T, int>::value)         return H5::PredType::NATIVE_INT;
  else if (std::is_same<T, float>::value)  return H5::PredType::NATIVE_FLOAT;
  else if (std::is_same<T, double>::value) return H5::PredType::NATIVE_DOUBLE;
  return H5::PredType::NATIVE_DOUBLE;
}

#include <fstream>
const std::string 
hdaq::interface::get_h5fname(const std::string& name, const unsigned int i) {
  const std::string fname = i? name + std::to_string(i) + ".h5" : name + ".h5";
  std::ifstream fp(fname);
  if (!fp.is_open()) return fname;
  return get_h5fname(name, i + 1);
}
