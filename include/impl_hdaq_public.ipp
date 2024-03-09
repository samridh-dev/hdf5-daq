///////////////////////////////////////////////////////////////////////////////

hdaq::interface::interface(const std::string& fname) :
  file(get_h5fname(fname), H5F_ACC_TRUNC) 
{}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void 
hdaq::interface::insert(const std::vector<T>& vec, const std::string& fname) {
  const std::pair<std::string, std::string> pathname = get_h5pathname(fname);
  const std::string path = pathname.first;
  const std::string name = pathname.second;
  (void)path;
  try {
    H5::Exception::dontPrint();
    if(map_dset.find(name) == map_dset.end()) {
      dset_write<T>(vec, name);
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

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void 
hdaq::interface::insert(
  const struct attribute<T>& attr,
  const std::string& fname
) {
  const std::pair<std::string, std::string> pathname = get_h5pathname(fname);
  const std::string path = pathname.first;
  const std::string name = pathname.second;
  (void)path;

  try {
    H5::Exception::dontPrint();
    if(map_dset.find(name) == map_dset.end()) {
      throw std::runtime_error("dataset not found");
    }

    const std::array<hsize_t, 1> dims{{attr.size()}};

    H5::DataSet& dset = map_dset[fname];
    H5::DataSpace adspace(1, dims.data());

    H5::Attribute md = dset.createAttribute(attr.name, get_h5type<T>(), adspace);
    md.write(get_h5type<T>(), attr.data());

  } catch (H5::FileIException error) {
    error.printErrorStack();
  } catch (H5::DataSetIException error) {
    error.printErrorStack();
  } catch (H5::DataSpaceIException error) {
    error.printErrorStack();
  }
}

///////////////////////////////////////////////////////////////////////////////
