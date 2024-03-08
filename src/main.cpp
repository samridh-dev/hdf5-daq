#include <hdaq.hpp>

#include <cmath>
#include <iostream>
constexpr size_t N = 10;
int main() {

  std::vector<float>a(N);
  for (int i = 0; i < a.size(); i++) a[i] = i*i * 1.0f / (a.size() * a.size());

  std::vector<double>b(N);
  for (int i = 0; i < b.size(); i++) b[i] = std::sqrt(i) / b.size();

  std::vector<int>md(8);
  for (int i = 0; i < md.size(); i++) md[i] = i;

  class hdaq::interface interface("dat/data");
  interface.insert(a, "square func");
  interface.insert(b, "square func");

  interface.insert(b, "root func");

  interface.add_attr(md, "metadata", "square func");

  for (int i = 0; i < md.size(); i++) md[i] = -i;
  interface.add_attr(md, "metadata 2", "square func");

  return 0;
}

