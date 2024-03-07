#ifndef HDF5_DAQ_HPP
#define HDF5_DAQ_HPP

#include <vector>
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

      template <typename T>
      constexpr H5::PredType get_h5predtype();

      const std::string 
      get_h5fname(const std::string& name, const unsigned int i = 0);
  };
}
#include <hdaq_impl.ipp>

#endif
