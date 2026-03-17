#include <iomanip>
#include <iostream>
#include <utility>
#include "top-it-vector.hpp"

bool testDefaultVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char *, test_t >;
  pair_t tests[] = {
      {"Default vector should be empty", testDefaultVector},
  };
  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  for (size_t i = 0; i < count; ++i) {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << '\n';
  }
}
