#ifndef HDF5_DAQ_HPP
#define HDF5_DAQ_HPP

#include <vector>
#include <array>
#include <utility>
#include <map>

#include <fstream>

#include <H5Cpp.h>

namespace hdaq {

  /**
   * @class interface
   * @brief Class for handling new hdf5 files 
   *
   * This class provides methods for creating HDF5 files, and provides a simple
   * interface to write datasets and attributes for said datasets
   */
  class interface {
    public:

      /**
       * @brief Creates a new HDF5 file
       * @param Name of file without extension. Note: if file exists, then an
       * index is appened to the end of fname
       */
      interface(const std::string& fname);

      /**
       * @brief Main interfacing function. 
       * @param vec   : data vector to append to dataset
       * @param fname : name of dataset to append data to
       * @tparam T    : vec type
       */
      template <typename T>
      void insert(const std::vector<T>& vec, const std::string& fname);

      /**
       * @brief Main interfacing function. Note: Dataset must already exist 
       * when inserting attributes.
       * @param avec  : attribute vector to append to dataset
       * @param aname : name of attribute
       * @param fname : name of dataset to attribute
       * @tparam T    : avec type
       */
      template <typename T>
      void add_attr(
        const std::vector<T>& avec,
        const std::string& aname,
        const std::string& fname
      );

    private:
      H5::H5File file;

      std::map<std::string, H5::DataSet> map_dset;

      template <typename T>
      constexpr H5::PredType get_h5type();
      
      /// get non-conflicting HDF5 filename
      const std::string 
      get_h5fname(const std::string& name, const unsigned int i = 0);

      /// get HDF5 name and path of given name
      const std::pair<std::string, std::string>
      get_h5pathname(const std::string& name);

      /// creates a new dataset
      template <typename T>
      H5::DataSet dset_create(const std::string& name, const size_t size);

      /// writes to dataset
      template <typename T>
      void dset_write(const std::vector<T>& vec, const std::string& name);

      /// appends to preexisting dataset
      template <typename T>
      void dset_append(const std::vector<T>& vec, const std::string& name);

  };
}
#include <impl_hdaq.ipp>

#endif
