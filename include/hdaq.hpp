#ifndef HDF5_DAQ_HPP
#define HDF5_DAQ_HPP

#include <vector>
#include <array>
#include <utility>
#include <map>

#include <fstream>

// main library
#include <H5Cpp.h>

namespace hdaq {
  template <typename T>
  class attribute: public std::vector<T> {
    public:
      attribute(const std::string& n);
      attribute(const std::string& n, const size_t size);
      attribute(const std::string& n, const std::initializer_list<T> ilist);
      
      attribute<T>& operator=(const std::vector<T>& other);
      attribute<T>& operator=(const T other);

      const std::string name() const;

    private:
      const std::string attr_name;
  };
}
#include <attribute.ipp>

namespace hdaq {
  template <typename T>
  class dataset: public std::vector<T> {
    public:
      dataset();
      dataset(const size_t size);
      dataset(const std::initializer_list<T> ilist);

      dataset<T>& operator=(const std::vector<T>& other);
      dataset<T>& operator=(const T other);
  };
}
#include <dataset.ipp>

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
      void insert(const class dataset<T>& data, const std::string& fname);

      /**
       * @brief Main interfacing function. Note: Dataset must already exist 
       * when inserting attributes.
       * @param attr  : attribute class
       * @param fname : name of dataset to write attribute to
       * @tparam T    : attr type
       */
      template <typename T>
      void insert(const class attribute<T>& attr, const std::string& fname);

    private:
      H5::H5File file;
      std::map<std::string, H5::DataSet> map_dset;

      /**
       * @brief Get the HDF5 data type for a given C++ data type.
       * @return H5::PredType HDF5 data type.
       * @tparam T C++ data type.
       */      
      template <typename T>
      const H5::PredType get_h5type();
      
      /**
       * @brief Generate a HDF5-compatible file name from a given name.
       * @param name Base name to convert.
       * @param i index to append to the name.
       * @return const std::string Generated HDF5 file name.
       */
      const std::string 
      get_h5fname(const std::string& name, const unsigned int i = 0);

      /**
       * @brief Parse a dataset name into its path and name components.
       * @param name Full dataset name.
       * @return const std::pair<std::string, std::string> Pair of path and
       * dataset name.
       */
      const std::pair<std::string, std::string>
      get_h5pathname(const std::string& name);

      /**
       * @brief Create a dataset within the HDF5 file.
       * @param name Name of the dataset to create.
       * @param size Initial size of the dataset.
       * @return H5::DataSet The created dataset object.
       * @tparam T Data type of the dataset.
       */
      template <typename T>
      H5::DataSet dset_create(const std::string& name, const size_t size);

      /**
       * @brief Write a vector of data to a dataset.
       * @param vec Vector of data to write.
       * @param name Name of the dataset to write to.
       * @tparam T Type of data in the vector.
       */
      template <typename T>
      void dset_write(const class dataset<T>& vec, const std::string& name);

      /**
       * @brief Append a vector of data to a dataset.
       * @param vec Vector of data to append.
       * @param name Name of the dataset to append to.
       * @tparam T Type of data in the vector.
       */
      template <typename T>
      void dset_append(const class dataset<T>& vec, const std::string& name);

  };
}

#include <impl_hdaq_public.ipp>
#include <impl_hdaq_private.ipp>

#endif
