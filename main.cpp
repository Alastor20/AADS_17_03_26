#include <iostream>
#include <utility>
#include "top-it-vector.hpp"

bool testDefaultVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}
bool testVectorWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return !v.isEmpty();
}

bool testSize()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return v.getSize() == 1;
}

bool testCapasity()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(1);
  v.popBack();
  return v.getCapasity();
}

bool testCopyConstructor()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  bool isAllEqual = v.getSize() == yav.getSize();
  for (size_t i = 0; i < v.getSize() && isAllEqual; ++i) {
    isAllEqual = isAllEqual && v[i] == yav[i];
  }
  return isAllEqual;
}

bool testElementAccses()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return (v[0] == 1) && (v[1] == 2);
}

bool testPushFront()
{
  topit::Vector< int > v;
  v.pushFront(1);
  v.pushFront(2);
  return v[0] == 2 && v[1] == 1;
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char *, test_t >;
  pair_t tests[] = {{"Default vector should be empty", testDefaultVector},
                    {"Vector with any value is not empty", testVectorWithValue},
                    {"Vector should change size on push", testSize},
                    {"Vector shoud keep cap after pop", testCapasity},
                    {"Test correct accses to elements", testElementAccses},
                    {"Vectors should be equal", testCopyConstructor},
                    {"Push front should paste in begining of vector", testPushFront}};
  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i) {
    bool res = tests[i].second();
    std::cout << (res ? "\033[92m" : "\033[31m") << res;
    std::cout << "\033[0m" << ": " << tests[i].first << '\n';
    pass = pass && res;
  }
  std::cout << (pass ? "\033[92m" : "\033[31m") << pass << "\033[0m" << ": RESULT" << '\n';
}
