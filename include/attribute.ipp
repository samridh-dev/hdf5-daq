//////////////////////////////////////////////////////////////////////////////

template <typename T>
hdaq::attribute<T>::attribute(const std::string& n) : 
  std::vector<T>(), attr_name(n) {}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
hdaq::attribute<T>::attribute(const std::string& n, const size_t size) : 
  std::vector<T>(size), attr_name(n) {}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
hdaq::attribute<T>::attribute(
  const std::string& n,
  std::initializer_list<T> ilist
) : std::vector<T>(ilist), attr_name(n) {}

//////////////////////////////////////////////////////////////////////////////

// operator overloading
template <typename T>
hdaq::attribute<T>& 
hdaq::attribute<T>::operator=(const std::vector<T>& other) {
  if (this != &other) {
    std::vector<T>::operator=(other);
  }
  return *this;
}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
hdaq::attribute<T>& 
hdaq::attribute<T>::operator=(const T other) {
  (*this).clear();
  (*this).push_back(other);
  return *this;
}

//////////////////////////////////////////////////////////////////////////////

template <typename T>
const std::string 
hdaq::attribute<T>::name() const {
  return attr_name;
}

//////////////////////////////////////////////////////////////////////////////
