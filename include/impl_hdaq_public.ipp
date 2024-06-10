///////////////////////////////////////////////////////////////////////////////
/// Interface Public Methods Implementations
///////////////////////////////////////////////////////////////////////////////

/* ------------------------------------------------------------------------- */

hdaq::interface::interface() :
  file(get_h5fname(""), H5F_ACC_TRUNC)
{}

/* ------------------------------------------------------------------------- */

hdaq::interface::interface(const std::string& fname) :
  file(get_h5fname(fname), H5F_ACC_TRUNC) 
{}

/* ------------------------------------------------------------------------- */

void hdaq::interface::set_filename(const std::string& fname) {
  if (file.getId() != H5I_BADID) {
    file.close();
  }
  file.openFile(get_h5fname(fname), H5F_ACC_RDWR);
}

/* ------------------------------------------------------------------------- */

template <typename T>
void 
hdaq::interface::insert(const class dataset<T>& vec, const std::string& fname) {
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

/* ------------------------------------------------------------------------- */

template <typename T>
void 
hdaq::interface::insert(
  const class attribute<T>& attr,
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

    H5::Attribute md = dset.createAttribute(
      attr.name(), get_h5type<T>(), adspace
    );
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
/// End
///////////////////////////////////////////////////////////////////////////////
