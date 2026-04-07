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

bool testElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

bool testElementConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  const topit::Vector< int > &rv = v;
  return rv[0] == 1 && rv[1] == 2;
}

bool testElementOutOfBoundCheckedAccess()
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

bool testElementInboundCheckedAccess()
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

bool testElementOutOfBoundCheckedConstAccess()
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

bool testElementInboundCheckedConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int > &rv = v;
  try {
    const int &val = rv.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
}

bool testCopyConstructor()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  bool isAllEqual = v.getSize() == yav.getSize();
  for (size_t i = 0; isAllEqual && i < v.getSize(); ++i) {
    isAllEqual = isAllEqual && (v[i] == yav[i]);
  }
  return isAllEqual;
}

bool testSwap()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > r;
  r.pushBack(2);
  v.swap(r);
  return r[0] == 1 && v[0] == 2;
}

bool testPushFront()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushFront(3);
  return v[0] == 3 && v[1] == 1 && v[2] == 2;
}

bool testDoublePushFront()
{
  topit::Vector< int > v;
  v.pushFront(1);
  v.pushFront(2);
  return v[0] == 2 && v[1] == 1;
}

bool testCapacityOfEmpty()
{
  topit::Vector< int > v;
  return !v.getCapasity();
}

bool testCapacityWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return v.getCapasity() == 1;
}

bool testCapacityWithMoreValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  return v.getCapasity() == 4;
}

bool testSizeOFEmpty()
{
  topit::Vector< int > v;
  return !v.getSize();
}

bool testSizeWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return v.getSize() == 1;
}

bool testPopBackWithEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.popBack();
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testPopBackWithOneValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    v.popBack();
    return v.isEmpty();
  } catch (...) {
    return false;
  }
}

bool testPopBackWithMoreValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try {
    v.popBack();
    return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
  } catch (...) {
    return false;
  }
}

bool testPopFrontWithEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.popFront();
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testPopFrontWithOneValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    v.popFront();
    return v.isEmpty();
  } catch (...) {
    return false;
  }
}

bool testPopFrontWithMoreValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try {
    v.popFront();
    return v[0] == 2 && v[1] == 3;
  } catch (...) {
    return false;
  }
}

bool testInsertValueInEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.insert(0, 1);
    return !v.isEmpty() && v[0] == 1;
  } catch (...) {
    return false;
  }
}

bool testInsertValueInVectorWithOneValue()
{
  topit::Vector< int > v1;
  v1.pushBack(2);
  topit::Vector< int > v2;
  v2.pushBack(2);
  try {
    v1.insert(0, 1);
    bool res = v1[0] == 1;
    v2.insert(1, 3);
    return res && v2[1] == 3;
  } catch (...) {
    return false;
  }
}

bool testInsertValueInVectorWithManyValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try {
    v.insert(1, 4);
    return v[0] == 1 && v[1] == 4 && v[2] == 2 && v[3] == 3;
  } catch (...) {
    return false;
  }
}

bool testInsertValueOutOfRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try {
    v.insert(10, 1);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseValueFromEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.erase(0);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseValueFromVectorWithOneValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    v.erase(0);
    return v.isEmpty();
  } catch (...) {
    return false;
  }
}

bool testEraseValueFromVectorWithManyValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  try {
    v.erase(2);
    bool res = v[0] == 1;
    res = res && v[1] == 2;
    res = res && v[2] == 4;
    return res && v.getSize() == 3;
  } catch (...) {
    return false;
  }
}

bool testEraseValueOutOfRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try {
    v.erase(5);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertRangeFromEmpty()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  topit::Vector< int > v2;
  try {
    v1.insert(0, v2, 0, 0);
    return v1[0] == 1;
  } catch (...) {
    return false;
  }
}

bool testInsertRangeInEmpty()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  topit::Vector< int > v2;
  try {
    v2.insert(0, v1, 0, 2);
    return !v2.isEmpty() && v2[0] == 1 && v2[1] == 2;
  } catch (...) {
    return false;
  }
}

bool testInsertRangeV1SizeLessV2Range()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  topit::Vector< int > v2;
  v2.pushBack(3);
  v2.pushBack(4);
  v2.pushBack(5);
  v2.pushBack(6);
  try {
    v1.insert(1, v2, 1, 4);
    bool res = v1[0] == 1;
    res = res && v1[1] == 4;
    res = res && v1[2] == 5;
    res = res && v1[3] == 6;
    res = res && v1[4] == 2;
    return res;
  } catch (...) {
    return false;
  }
}

bool testInsertRangeV1SizeMoreV2Range()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector< int > v2;
  v2.pushBack(5);
  v2.pushBack(6);
  v2.pushBack(7);
  v2.pushBack(8);
  try {
    v1.insert(2, v2, 1, 3);
    bool res = v1[0] == 1;
    res = res && v1[1] == 2;
    res = res && v1[2] == 6;
    res = res && v1[3] == 7;
    res = res && v1[4] == 3;
    res = res && v1[5] == 4;
    return res;
  } catch (...) {
    return false;
  }
}

bool testInsertRangeIndexOutOfRange()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector< int > v2;
  v2.pushBack(5);
  v2.pushBack(6);
  v2.pushBack(7);
  v2.pushBack(8);
  try {
    v1.insert(10, v2, 1, 3);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertRangeBeginMoreThanEnd()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector< int > v2;
  v2.pushBack(5);
  v2.pushBack(6);
  v2.pushBack(7);
  v2.pushBack(8);
  try {
    v1.insert(2, v2, 2, 1);
    return false;
  } catch (const std::range_error &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertRangeEndOutOfRange()
{
  topit::Vector< int > v1;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v1.pushBack(4);
  topit::Vector< int > v2;
  v2.pushBack(5);
  v2.pushBack(6);
  v2.pushBack(7);
  v2.pushBack(8);
  try {
    v1.insert(0, v2, 0, 10);
    return false;
  } catch (const std::range_error &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseRangeFromEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.erase(0, 1);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseRangeFromVectorWithOneValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    v.erase(0, 1);
    return v.isEmpty();
  } catch (...) {
    return false;
  }
}

bool testEraseRangeFromVectorWithManyValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  try {
    v.erase(1, 4);
    return v[0] == 1 && v[1] == 5;
  } catch (...) {
    return false;
  }
}

bool testEraseRangeWhenEndMoreThanSize()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  try {
    v.erase(0, 5);
    return false;
  } catch (const std::range_error &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseRangeWhenBeginMoreThanEnd()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    v.erase(1, 0);
    return false;
  } catch (const std::range_error &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertFwdItersEmptyVector()
{
  topit::Vector< int > v1, v2;
  v2.pushBack(1);
  v2.pushBack(2);
  v2.pushBack(3);
  try {
    v1.insert(v1.begin(), v2.begin(), v2.end());
    return !v1.isEmpty() && v1[0] == 1 && v1[1] == 2 && v1[2] == 3;
  } catch (...) {
    return false;
  }
}

bool testInsertFwdItersBegEqEnd()
{
  topit::Vector< int > v1, v2;
  try {
    v1.insert(v1.begin(), v2.begin(), v2.end());
    return v1.isEmpty();
  } catch (...) {
    return false;
  }
}

bool testInsertFwdItersPosIncorrect()
{
  topit::Vector< int > v1, v2;
  v2.pushBack(1);
  v2.pushBack(2);
  v2.pushBack(3);
  try {
    v1.insert(v1.begin() + 1, v2.begin(), v2.end());
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertFwdItersNormal()
{
  topit::Vector< int > v1, v2;
  v1.pushBack(1);
  v1.pushBack(2);
  v1.pushBack(3);
  v2.pushBack(4);
  v2.pushBack(5);
  v2.pushBack(6);
  v2.pushBack(7);
  try {
    v1.insert(++v1.begin(), v2.begin() + 1, v2.begin() + 3);
    bool res = v1.getSize() == 5;
    res = v1[0] == 1;
    res = res && v1[1] == 5;
    res = res && v1[2] == 6;
    res = res && v1[3] == 2;
    res = res && v1[4] == 3;
    return res;
  } catch (...) {
    return false;
  }
}

bool testInitializerListConstructor()
{
  topit::Vector< int > v{1, 2};
  return v.getSize() == 2;
}

bool testInsertIterOneValueEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.insert(v.begin(), 1);
    return v.getSize() == 1 && v[0] == 1;
  } catch (...) {
    return false;
  }
}

bool testInsertIterOneValueNormal()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.insert(v.begin() + 1, 4);
    return v.getSize() == 4 && v[0] == 1 && v[1] == 4 && v[2] == 2 && v[3] == 3;
  } catch (...) {
    return false;
  }
}

bool testInsertIterOneValueIncorrectPos()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.insert(v.begin() + 5, 4);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertIterManyValueEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.insert(1, 2, v.begin());
    return v.getSize() == 2 && v[0] == 1 && v[1] == 1;
  } catch (...) {
    return false;
  }
}

bool testInsertIterMoreValueNormal()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.insert(4, 3, v.begin() + 2);
    bool res = v.getSize() == 6;
    res = res && v[0] == 1 && v[1] == 2;
    res = res && v[2] == 4 && v[3] == 4;
    res = res && v[4] == 4 && v[5] == 3;
    return res;
  } catch (...) {
    return false;
  }
}

bool testInsertIterManyValueIncorrectPos()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.insert(4, 5, v.begin() + 5);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseIterRangeEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.erase(v.begin(), v.end());
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseIterRangeOneElement()
{
  topit::Vector< int > v{1};
  try {
    v.erase(v.begin(), v.end());
    return v.isEmpty();
  } catch (...) {
    return false;
  }
}

bool testEraseIterRangeEndPosMoreThenSize()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.erase(v.begin(), v.end() + 1);
    return false;
  } catch (const std::range_error &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseIterRangeBegMoreThanEnd()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.erase(v.end(), v.begin());
    return false;
  } catch (const std::range_error &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseIterRangeNormal()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  try {
    v.erase(v.begin() + 1, v.begin() + 3);
    return v.getSize() == 3 && v[0] == 1 && v[1] == 4 && v[2] == 5;
  } catch (...) {
    return false;
  }
}

bool testEraseIterOneEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.erase(v.begin());
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseIterOneVectorWithOneElem()
{
  topit::Vector< int > v{1};
  try {
    v.erase(v.begin());
    return v.isEmpty();
  } catch (...) {
    return false;
  }
}

bool testEraseIterOneVectorWithManyElems()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.erase(v.begin() + 1);
    return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
  } catch (...) {
    return false;
  }
}

bool testEraseIterOneIncorrectPos()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.erase(v.end());
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseIterCountEmptyVector()
{
  topit::Vector< int > v;
  try {
    v.erase(v.begin(), 2);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseIterCountOneElem()
{
  topit::Vector< int > v{1};
  try {
    v.erase(v.begin(), 1);
    return v.isEmpty();
  } catch (...) {
    return false;
  }
}

bool testEraseIterCountManyElem()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  try {
    v.erase(v.begin() + 1, 3);
    return v.getSize() == 2 && v[0] == 1 && v[1] == 5;
  } catch (...) {
    return false;
  }
}

bool testEraseIterCountPosPlusCountMoreThenSize()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.erase(v.begin(), 5);
    return false;
  } catch (const std::range_error &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testShrinkToFit()
{
  topit::Vector< int > v{1, 2, 3};
  v.reserve(6);
  v.shrinkToFit();
  return v.getCapasity() == 3 && v.getCapasity() == v.getSize();
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char *, test_t >;
  pair_t tests[] = {
      {"Default vector should be empty", testDefaultVector},
      {"Vector with any value is not empty", testVectorWithValue},
      {"Inbound access elements", testElementAccess},
      {"Sizes must be equal as elements", testCopyConstructor},
      {"The data is valid when swapping places", testSwap},
      {"The element should be added to the beginning", testPushFront},
      {"Correctly adding two elements to the beginning", testDoublePushFront},
      {"Capacity of the empty vector is 0", testCapacityOfEmpty},
      {"Capacity of a non-empty vector is correct", testCapacityWithValue},
      {"Size of the empty vector is 0", testSizeOFEmpty},
      {"Size of a non-empty vector is correct", testSizeWithValue},
      {"Deleting from an empty vector generates a certain exception (popBack)", testPopBackWithEmptyVector},
      {"Deleting a vector with one value makes it empty (popBack)", testPopBackWithOneValue},
      {"Deleting from a vector reduces its size and keeps the data correct (popBack)", testPopBackWithMoreValues},
      {"Deleting from an empty vector generates a certain exception (popFront)", testPopFrontWithEmptyVector},
      {"Deleting a vector with one value makes it empty (popFront)", testPopFrontWithOneValue},
      {"Deleting from a vector reduces its size and keeps the data correct (popFront)", testPopFrontWithMoreValues},
      {"The correct expansion of the array capacity by 2 times is expected", testCapacityWithMoreValues},
      {"If an element exists, it returns the correct answer in a const vector", testElementInboundCheckedConstAccess},
      {"at(0) will throw an exception for an empty const vector", testElementOutOfBoundCheckedConstAccess},
      {"If an element exists, it returns the correct answer", testElementInboundCheckedAccess},
      {"at(0) will throw an exception for an empty vector", testElementOutOfBoundCheckedAccess},
      {"Inbound access elements in const vector", testElementConstAccess},
      {"Inserting into an empty vector", testInsertValueInEmptyVector},
      {"Inserting at the beginning and end of a vector with a single value", testInsertValueInVectorWithOneValue},
      {"Insertion into the vector", testInsertValueInVectorWithManyValues},
      {"Inserting an element outside the border throws an exception", testInsertValueOutOfRange},
      {"Erase from empty vector throws an exception", testEraseValueFromEmptyVector},
      {"Erase from vector with one value make it empty", testEraseValueFromVectorWithOneValue},
      {"Erase from empty vector with values its size decreases", testEraseValueFromVectorWithManyValues},
      {"Erase from out of range throw an exception", testEraseValueOutOfRange},
      {"Insert from empty dont change vector", testInsertRangeFromEmpty},
      {"Insert in empty push back elems", testInsertRangeInEmpty},
      {"Insert in vector with size less than paste range from v2", testInsertRangeV1SizeLessV2Range},
      {"Insert in vector with size more than paste range from v2", testInsertRangeV1SizeMoreV2Range},
      {"Insert range in vector when index more than size throw an exception", testInsertRangeIndexOutOfRange},
      {"Insert range in vector when begin more than end throw an exception", testInsertRangeBeginMoreThanEnd},
      {"Insert range in vector when end more than size throw an exception", testInsertRangeEndOutOfRange},
      {"Erase range from empty vector throw an exception", testEraseRangeFromEmptyVector},
      {"Erase range from vector with one value make it empty", testEraseRangeFromVectorWithOneValue},
      {"Erase range from vector with many values is correct", testEraseRangeFromVectorWithManyValues},
      {"Erase range when end more than size throw an exception", testEraseRangeWhenEndMoreThanSize},
      {"Erase range when begin more than end throw an exception", testEraseRangeWhenBeginMoreThanEnd},
      {"Insert in empty vector add elems in it", testInsertFwdItersEmptyVector},
      {"Insert when beg == end not change vector", testInsertFwdItersBegEqEnd},
      {"Insert when pos is incorrect throw an exception", testInsertFwdItersPosIncorrect},
      {"Correct insertion with iterators", testInsertFwdItersNormal},
      {"Vector with initializer list must be same size as init-list", testInitializerListConstructor},
      {"Insert in empty vector add elem in it", testInsertIterOneValueEmptyVector},
      {"Correct insertion in vector", testInsertIterOneValueNormal},
      {"Insertion in incorrect pos throw an exception", testInsertIterOneValueIncorrectPos},
      {"Insert in empty vector add elem in it (many)", testInsertIterManyValueEmptyVector},
      {"Correct insertion in vector (many)", testInsertIterMoreValueNormal},
      {"Insertion in incorrect pos throw an exception (many)", testInsertIterManyValueIncorrectPos},
      {"Erase from empty vector throw an exception (range iters)", testEraseIterRangeEmptyVector},
      {"Erase from vector with one elem make it empty (range iters)", testEraseIterRangeOneElement},
      {"Erase when end pos more than size throw an exception (range iters)", testEraseIterRangeEndPosMoreThenSize},
      {"Erase when beg pos more than end pos throw an exception (range iters)", testEraseIterRangeBegMoreThanEnd},
      {"Correct result of normal erasing (range iters)", testEraseIterRangeNormal},
      {"Erase from empty vector throw an exception (one iter)", testEraseIterOneEmptyVector},
      {"Erase from vector with one elem make it empty (one iter)", testEraseIterOneVectorWithOneElem},
      {"Erase from vector with many elem delete elem from it (one iter)", testEraseIterOneVectorWithManyElems},
      {"Erase from vector with incorrect pos throw an exception (one iter)", testEraseIterOneIncorrectPos},
      {"Erase from empty vector throw an exception (iter + count)", testEraseIterCountEmptyVector},
      {"Erase one elem make vector is empty (iter + count)", testEraseIterCountOneElem},
      {"Erase many elem remove they (iter + count)", testEraseIterCountManyElem},
      {"Erase when pos + count more than size throw an exception", testEraseIterCountPosPlusCountMoreThenSize},
      {"Make capacity equal to size", testShrinkToFit},
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
