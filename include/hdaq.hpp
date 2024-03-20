#ifndef HDF5_DAQ_HPP
#define HDF5_DAQ_HPP

///////////////////////////////////////////////////////////////////////////////

/**
\mainpage HDF5 Data Acquisition Library (HDAQ) Documentation

# Overview

The HDF5 Data Acquisition Library (HDAQ) is designed to facilitate the
management and manipulation of HDF5 files within C++ applications, particularly
those used in scientific research and data acquisition systems. HDF5 files are
renowned for their ability to store large volumes of complex data efficiently.
This library provides a simplified and intuitive interface for creating and
managing HDF5 datasets and attributes, enhancing the ease of integrating HDF5
file operations into applications.

# Key Features

- **Attribute Management**: Offers an extension of `std::vector` to manage
attributes for HDF5 datasets. Attributes can include metadata such as units,
descriptions, and other ancillary information, enhancing the
self-descriptiveness of datasets.

- **Dataset Management**: Provides a specialized container, extending
`std::vector`, designed for efficient management of datasets within HDF5 files.
It supports various operations including creation, initialization, and
assignment of datasets.

- **HDF5 File Interface**: Facilitates the creation and management of HDF5
files, including the capabilities to write datasets and attributes, with
support for unique file naming to prevent overwrites.

# Components

## attribute

A template class extending `std::vector`, designed for managing attributes
related to datasets in HDF5 files. It supports storing metadata that describes
the datasets, improving data self-descriptiveness.

## dataset

Another template class extending `std::vector`, aimed at dataset management
within HDF5 files. It simplifies dataset creation, initialization, and
manipulation.

## interface

The core class that manages HDF5 file operations, including creating files, as
well as writing datasets and attributes. It serves as the primary interface for
interacting with HDF5 files.

# Getting Started

To use the HDAQ library, include the main header (`hdaq.hpp`) in your
project. Instantiate and utilize the `attribute`, `dataset`, and `interface`
classes as needed to manage HDF5 files according to your application's
requirements.

For detailed examples and further information on using each component of the
library, refer to the specific sections of this documentation.

# Note
For additional reference on implementing hdf5 files please refer to the source:
<a href="https://docs.hdfgroup.org/hdf5/develop/_h_d_f5_examples.html">
HDF5 Examples
</a>

*/

///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <array>
#include <utility>
#include <map>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////

#include <H5Cpp.h>

///////////////////////////////////////////////////////////////////////////////
namespace hdaq {
  /**
   * @class attribute
   * @brief Extends std::vector to manage attributes for HDF5 datasets.
   *
   * This class inherits from std::vector, providing a container specifically
   * designed for managing attributes in HDF5 files. Attributes can be used to
   * store metadata for datasets, such as units, descriptions, or other
   * ancillary information. The class includes constructors for initializing
   * attributes with various types of data, operator overloads for convenient
   * assignment, and a member function to access the attribute's name.
   *
   * @tparam T Data type of the elements in the attribute.
   */
  template <typename T>
  class attribute: public std::vector<T> {
    public:
      /**
       * @brief Constructs an attribute with a specified name. The attribute is
       * initially empty.
       * @param n Name of the attribute.
       */
      attribute(const std::string& n);

      /**
       * @brief Constructs an attribute with a specified name and size.
       * Elements are default-initialized.
       * @param n Name of the attribute.
       * @param size Initial size of the attribute.
       */
      attribute(const std::string& n, const size_t size);

      /**
       * @brief Constructs an attribute from an existing std::vector, with a
       * specified name.
       * @param n Name of the attribute.
       * @param vec A vector object to initialize the attribute.
       */
      attribute(const std::string& n, const std::vector<T>& vec);

      /**
       * @brief Constructs an attribute from an initializer list, with a
       * specified name.
       * @param n Name of the attribute.
       * @param ilist An initializer list to initialize the attribute.
       */
      attribute(const std::string& n, const std::initializer_list<T> ilist);
      
      /**
       * @brief Assigns the values of an existing std::vector to this
       * attribute.
       * @param other A vector object whose values are to be assigned to this
       * attribute.
       * @return Reference to this attribute after assignment.
       */
      attribute<T>& operator=(const std::vector<T>& other);

      /**
       * @brief Assigns a single value to all elements in the attribute.
       * @param other The value to assign to all elements of the attribute.
       * @return Reference to this attribute after assignment.
       */
      attribute<T>& operator=(const T other);

      /**
       * @brief Retrieves the name of the attribute.
       * @return Name of the attribute as a const std::string.
       */
      const std::string name() const;

    private:
      const std::string attr_name; ///< Name of the attribute.
  };
}
#include <attribute.ipp>

///////////////////////////////////////////////////////////////////////////////

namespace hdaq {
  /**
   * @class dataset
   * @brief Extends std::vector for specialized dataset management in HDF5
   * files.
   *
   * This class inherits from std::vector, providing a container specifically
   * designed for managing datasets within HDF5 files. It includes constructors
   * for initializing datasets in various ways and operator overloads for
   * dataset assignment.
   *
   * @tparam T Data type of the elements in the dataset.
   */
  template <typename T>
  class dataset: public std::vector<T> {
    public:
      /**
       * @brief Default constructor. Creates an empty dataset.
       */
      dataset();

      /**
       * @brief Constructs a dataset with a specified size. Elements are
       * default-initialized.
       * @param size Initial size of the dataset.
       */
      dataset(const size_t size);

      /**
       * @brief Constructs a dataset from an existing std::vector.
       * @param vec A vector object to initialize the dataset.
       */
      dataset(const std::vector<T>& vec);

      /**
       * @brief Constructs a dataset from an initializer list.
       * @param ilist An initializer list to initialize the dataset.
       */
      dataset(const std::initializer_list<T> ilist);

      /**
       * @brief Assigns the values of an existing std::vector to this dataset.
       * @param other A vector object whose values are to be assigned to this
       * dataset.
       * @return Reference to this dataset after assignment.
       */
      dataset<T>& operator=(const std::vector<T>& other);

      /**
       * @brief Assigns a single value to all elements in the dataset.
       * @param other The value to assign to all elements of the dataset.
       * @return Reference to this dataset after assignment.
       */
      dataset<T>& operator=(const T other);
  };
}
#include <dataset.ipp>

///////////////////////////////////////////////////////////////////////////////

namespace hdaq {
  /**
   * @class interface
   * @brief Manages HDF5 file creation and manipulation.
   *
   * Provides functionality to create and manage HDF5 files, including writing
   * datasets and attributes.
   */
  class interface {
    public:
      /**
       * @brief Constructor to create a new HDF5 file.
       * @param fname Name of the file without extension. Appends an index if
       * the file already exists.
       */
      interface(const std::string& fname);

      /**
       * @brief Creates a new dataset within the HDF5 file.
       * @note The size parameter defines the immutable size of the dataset.
       * Once set, all subsequent insertions must match this size exactly. This
       * design choice is made to avoid complications with irregular matrices,
       * ensuring datasets maintain consistent dimensions.
       * @param name Dataset name.
       * @param size Initial dataset size.
       * @return The created dataset object.
       * @tparam T Data type of the dataset.
       */
      template <typename T>
      H5::DataSet create_dataset(const std::string& name, const size_t size);

      /**
       * @brief Writes or appends data to a dataset.
       * @note The vector's size passed to this function must match the
       * dataset's immutable size established at creation or during the first
       * insertion. This ensures that all data within the dataset maintains
       * consistent dimensions, aligning with the library's design to not
       * handle irregular matrices.
       * @param dataset Vector to write or append.
       * @param fname Name of the dataset to which the vector will be written
       * or appended to. 
       * @tparam T Data type of the vector.
       */
      template <typename T>
      void insert(const class dataset<T>& data, const std::string& fname);

      /**
       * @brief Writes attributes to an existing dataset.
       * @note Before inserting attributes, the dataset must already exist
       * within the HDF5 file. This prerequisite can be satisfied by first
       * calling `create_dataset` to create a new dataset or using `insert`
       * with a dataset vector argument to write or append data to an existing
       * or new dataset. Attempting to insert attributes into a non-existent
       * dataset will result in an error. Ensure that the dataset has been
       * properly created or data has been inserted into it before adding
       * attributes to it.
       * @param attr Attribute to write
       * @param fname Name of the dataset to which the attribute will be added. 
       * @tparam T Attribute type.
       */
      template <typename T>
      void insert(const class attribute<T>& attr, const std::string& fname);

    private:
      H5::H5File file;                             ///< HDF5 file object.
      std::map<std::string, H5::DataSet> map_dset; ///< Map of dataset objects

      /**
       * @brief Determines the HDF5 data type corresponding to a C++ data type.
       * @return Corresponding HDF5 data type.
       * @tparam T C++ data type.
       */
      template <typename T>
      const H5::PredType get_h5type();
      
      /**
       * @brief Generates a unique HDF5 file name.
       * @param name Base file name.
       * @param i Index to append for uniqueness.
       * @return Generated HDF5 file name.
       */
      const std::string 
      get_h5fname(const std::string& name, const unsigned int i = 0);

      /**
       * @brief Splits a dataset name into path and name components.
       * @param name Full dataset name.
       * @return Pair containing the path and dataset name.
       */
      const std::pair<std::string,std::string>
      get_h5pathname(const std::string& name);


      /**
       * @brief Writes a vector of data to a dataset.
       * @param vec Data vector.
       * @param name Dataset name.
       * @tparam T Data type of the vector.
       */
      template <typename T>
      void dset_write(const class dataset<T>& vec, const std::string& name);

      /**
       * @brief Appends a vector of data to an existing dataset.
       * @param vec Data vector.
       * @param name Dataset name.
       * @tparam T Data type of the vector.
       */
      template <typename T>
      void dset_append(const class dataset<T>& vec, const std::string& name);
  };
}
#include <impl_hdaq_public.ipp>
#include <impl_hdaq_private.ipp>

///////////////////////////////////////////////////////////////////////////////
#endif
