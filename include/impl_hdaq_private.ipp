///////////////////////////////////////////////////////////////////////////////

template <typename T>
const H5::PredType 
hdaq::interface::get_h5type() {
  if (std::is_same<T, int>::value)         return H5::PredType::NATIVE_INT;
  else if (std::is_same<T, size_t>::value) return H5::PredType::NATIVE_HSIZE;
  else if (std::is_same<T, float>::value)  return H5::PredType::NATIVE_FLOAT;
  else if (std::is_same<T, double>::value) return H5::PredType::NATIVE_DOUBLE;
  else if (std::is_same<T, bool>::value)   return H5::PredType::NATIVE_HBOOL;
  return H5::PredType::NATIVE_DOUBLE;
}

///////////////////////////////////////////////////////////////////////////////

const std::string 
hdaq::interface::get_h5fname(const std::string& name, const unsigned int i) {
  const std::string fname = i? name + std::to_string(i) + ".h5" : name + ".h5";
  std::ifstream fp(fname);
  if (!fp.is_open()) return fname;
  return get_h5fname(name, i + 1);
}

///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
const std::pair<std::string, std::string>
hdaq::interface::get_h5pathname(const std::string& name) {
  const size_t split = name.find_last_of('/');
  if (split != std::string::npos) {
    const std::string fpath = name.substr(0,split + 1);
    const std::string fname = name.substr(split + 1);
    return std::make_pair(fpath, fname);
  }
  return std::make_pair("/",name);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
H5::DataSet
hdaq::interface::create_dataset(
  const std::string& name,
  const size_t size
) {

  std::array<hsize_t,2> dims{{size, 1}};
  std::array<hsize_t,2> maxdims{{size, H5S_UNLIMITED}};
  std::array<hsize_t,2> chunkdims{{size, 1}};

  H5::DataSpace dspace(dims.size(), dims.data(), maxdims.data());
  H5::DSetCreatPropList plist;
  plist.setChunk(chunkdims.size(), chunkdims.data());
  H5::DataSet dset = file.createDataSet(name, get_h5type<T>(), dspace, plist);
  map_dset[name] = dset;

  return dset;
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void
hdaq::interface::dset_write(
  const hdaq::dataset<T>& vec, 
  const std::string& name
) {
  H5::DataSet dset = create_dataset<T>(name, vec.size());
  dset.write(vec.data(), get_h5type<T>());
}

///////////////////////////////////////////////////////////////////////////////
 
template <typename T>
void
hdaq::interface::dset_append(
  const hdaq::dataset<T>& vec,
  const std::string& name
) {
  if(map_dset.find(name) == map_dset.end()) {
    throw std::runtime_error("dataset not found");
  }

  H5::DataSet& dset = map_dset[name];
  H5::DataSpace dspace = dset.getSpace();

  std::array<hsize_t,2>dims{{}};
  dspace.getSimpleExtentDims(dims.data(), nullptr);
  const std::array<hsize_t,2> ndims{{dims[0], dims[1] + 1}};
  const std::array<hsize_t,2> offs{{0, dims[1]}};
  const std::array<hsize_t,2> count{{dims[0], 1}};

  if (vec.size() != dims[0]) {
    throw std::runtime_error("vector is not of same size as dataset");
  }

  dset.extend(ndims.data());
  H5::DataSpace nspace = dset.getSpace();
  nspace.selectHyperslab(H5S_SELECT_SET, count.data(), offs.data());
  H5::DataSpace memspace(1, &dims[0]);
  dset.write(vec.data(), get_h5type<T>(), memspace, nspace);
}

///////////////////////////////////////////////////////////////////////////////
