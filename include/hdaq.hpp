#ifndef HDF5_DAQ_HPP
#define HDF5_DAQ_HPP

#include <vector>
#include <array>
#include <utility>
#include <map>

#include <fstream>

#include <H5Cpp.h>

namespace hdaq {
  class interface {
    public:
      interface(const std::string& fname);

      template <typename T>
      void insert(const std::vector<T>& vec, const std::string& fname);

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

      const std::string 
      get_h5fname(const std::string& name, const unsigned int i = 0);

      const std::pair<std::string, std::string>
      get_h5pathname(const std::string& name);

      template <typename T>
      H5::DataSet dset_create(const std::string& name, const size_t size);

      template <typename T>
      void dset_write(const std::vector<T>& vec, const std::string& name);

      template <typename T>
      void dset_append(const std::vector<T>& vec, const std::string& name);

  };
}
#include <impl_hdaq.ipp>

#endif
