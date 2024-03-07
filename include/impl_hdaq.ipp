hdaq::interface::interface(const std::string& filename) :
  file(get_h5fname(filename), H5F_ACC_TRUNC) 
{}

template <typename T>
void 
hdaq::interface::insert(const std::vector<T>& vec, const std::string& name) {
  try {
    H5::Exception::dontPrint();
    if(map_dset.find(name) == map_dset.end()) {
      dset_write<T>(vec, name);
      map_dset[name] = file.openDataSet(name);
    } else {
      dset_append<T>(vec, name);
    }
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
hdaq::interface::get_h5type() {
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

template <typename T>
void
hdaq::interface::dset_write(
  const std::vector<T>& vec, 
  const std::string& name
) {
  std::vector<hsize_t>dims{vec.size(), 1};
  std::vector<hsize_t>maxdims{vec.size(), H5S_UNLIMITED};
  std::vector<hsize_t>chunkdims{vec.size(), 1};
  H5::DataSpace dspace(dims.size(), dims.data(), maxdims.data());
  H5::DSetCreatPropList plist;
  plist.setChunk(chunkdims.size(), chunkdims.data());
  H5::DataSet dset = file.createDataSet(name, get_h5type<T>(), dspace, plist);
  dset.write(vec.data(), get_h5type<T>());
}

template <typename T>
void
hdaq::interface::dset_append(
  const std::vector<T>& vec,
  const std::string& name
) {
  if(map_dset.find(name) == map_dset.end()) {
    throw std::runtime_error("dataset not found");
  }
  H5::DataSet& dset = map_dset[name];
  H5::DataSpace dspace = dset.getSpace();
  std::vector<hsize_t>dims(2);
  dspace.getSimpleExtentDims(dims.data(), nullptr);

  const std::vector<hsize_t>ndims{dims[0], dims[1] + 1};
  dset.extend(ndims.data());

  H5::DataSpace nspace = dset.getSpace();
  const std::vector<hsize_t>offs{0, dims[1]};
  const std::vector<hsize_t>count{dims[0], 1};
  nspace.selectHyperslab(H5S_SELECT_SET, count.data(), offs.data());
  H5::DataSpace memspace(1, &dims[0]);
  dset.write(vec.data(), get_h5type<T>(), memspace, nspace);
}
