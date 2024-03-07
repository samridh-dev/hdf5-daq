#ifndef HDF5_DAQ_HPP
#define HDF5_DAQ_HPP

#include <vector>
#include <map>
#include <H5Cpp.h>

namespace hdaq {
  class interface {
    public:
      interface(const std::string& filename);

      template <typename T>
      void 
      insert(const std::vector<T>& vec, const std::string& name);

    private:
      H5::H5File file;

      std::map<std::string, H5::DataSet> map_dset;

      template <typename T>
      constexpr H5::PredType get_h5type();

      const std::string 
      get_h5fname(const std::string& name, const unsigned int i = 0);

      template <typename T>
      void
      dset_write(const std::vector<T>& vec, const std::string& name);

      template <typename T>
      void 
      dset_append(const std::vector<T>& vec, const std::string& name);

  };
}
#include <impl_hdaq.ipp>

#endif
