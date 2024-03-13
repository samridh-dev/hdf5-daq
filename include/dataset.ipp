///////////////////////////////////////////////////////////////////////////////

template <typename T> 
hdaq::dataset<T>::dataset() : 
  std::vector<T>() {}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
hdaq::dataset<T>::dataset(const size_t size) : 
  std::vector<T>(size) {}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
hdaq::dataset<T>::dataset(const std::initializer_list<T> ilist) :
  std::vector<T>(ilist) {}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
hdaq::dataset<T>&
hdaq::dataset<T>::operator=(const std::vector<T>& other) {
  if (this != &other) {
    std::vector<T>::operator=(other);
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////

template <typename T> 
hdaq::dataset<T>&
hdaq::dataset<T>::operator=(const T other) {
  (*this).clear();
  (*this).push_back(other);
  return *this;
}


///////////////////////////////////////////////////////////////////////////////