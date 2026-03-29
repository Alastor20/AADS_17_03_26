#include <iostream>
#include <stdexcept>
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
  return v.getSize() == 2;
}

bool testCapasityStay()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(1);
  v.popBack();
  return v.getCapasity() == 2;
}

bool testPop()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(1);
  v.popBack();
  return v.getSize() == 1;
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

bool testCopyOper()
{
  topit::Vector< int > v, vv;
  v.pushBack(1);
  vv = v;
  return v[0] == 1 && vv[0] == 1;
}

bool testSwap()
{
  topit::Vector< int > v, vv;
  v.pushBack(1);
  vv.pushBack(2);
  v.swap(vv);
  return v[0] == 2;
}

bool testElementAccses()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return (v[0] == 1) && (v[1] == 2);
}

bool testAccsesConst()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  const topit::Vector< int > rv = v;
  return (rv[0] == 1 && rv[1] == 2);
}

bool testCheckAccsesOut()
{
  topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testCheckAccsesIn()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    int &val = v.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
}

bool testCheckAccsesOutConst()
{
  const topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testCheckAccsesInConst()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int > rv = v;
  try {
    const int &val = rv.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
}
bool testPushFront()
{
  topit::Vector< int > v;
  v.pushFront(1);
  v.pushFront(2);
  return v[0] == 2 && v[1] == 1;
}

bool testInsertOutOfRange()
{
  try {
    topit::Vector< int > v;
    v.pushBack(1);
    v.insert(2, 2);
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
  return false;
}

bool testEraseOutOfRange()
{
  try {
    topit::Vector< int > v;
    v.pushBack(1);
    v.erase(2);
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
  return false;
}

bool testInsert()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.insert(1, 3);
  return v[1] == 3;
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char *, test_t >;
  pair_t tests[] = {
      {"Default vector should be empty", testDefaultVector},
      {"Vector with any value is not empty", testVectorWithValue},
      {"Vector should change size on push", testSize},
      {"getCap should return actual cap", testCapasity},
      {"copy should not change origin", testCopyOper},
      {"Vector shoud keep cap after pop", testCapasityStay},
      {"Pop shold change size", testPop},
      {"Test correct accses to elements", testElementAccses},
      {"Const thing", testAccsesConst},
      {"swap should swap vectors", testSwap},
      {"Vectors should be equal", testCopyConstructor},
      {"save accses out of bounds", testCheckAccsesOut},
      {"const var", testCheckAccsesOutConst},
      {"save accses in bounds", testCheckAccsesIn},
      {"const var", testCheckAccsesInConst},
      {"You cant insert past size+1", testInsertOutOfRange},
      {"You cant erase past size+1", testEraseOutOfRange},
      {"insert should actualy insert value", testInsert},
  };
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
