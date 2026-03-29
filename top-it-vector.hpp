#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cassert>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace topit
{
  template < class T >
  class Vector;

  template < class T >
  struct VIter
  {
    explicit VIter(Vector< T > &v, size_t pos);
    bool operator==(const VIter< T > &) const noexcept;
    bool operator!=(const VIter< T > &) const noexcept;
    VIter< T > &operator++() noexcept;
    VIter< T > &operator--() noexcept;
    T &operator*();

  private:
    Vector< T > &v_;
    size_t pos_;
  };

  template < class T >
  struct VCIter
  {
    explicit VCIter(const Vector< T > &v, size_t pos);
    bool operator==(const VCIter< T > &) const noexcept;
    bool operator!=(const VCIter< T > &) const noexcept;
    VCIter< T > &operator++() noexcept;
    VCIter< T > &operator--() noexcept;
    const T &operator*();

  private:
    const Vector< T > &v_;
    size_t pos_;
  };
  template < class T >
  class Vector
  {
  public:
    Vector();
    Vector(const Vector< T > &);
    Vector(Vector< T > &&) noexcept;
    Vector< T > &operator=(const Vector< T > &);
    Vector< T > &operator=(Vector< T > &&) noexcept;
    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;
    ~Vector();
    bool isEmpty() const noexcept;
    void pushBack(const T &);
    void popBack();
    size_t getSize() const noexcept;
    size_t getCapasity() const noexcept;
    void swap(Vector< T > &rhs) noexcept;
    void pushFront(const T &);
    void popFront();
    T &at(size_t id);
    const T &at(size_t id) const;
    void insert(size_t i, const T &val);
    void erase(size_t i);
    void insert(size_t i, const Vector< T > &rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);

    VIter< T > begin();
    VCIter< T > cbegin() const;
    VIter< T > end();
    VCIter< T > cend() const;

  private:
    T *data_;
    size_t size_, capasity_;
    explicit Vector(size_t k);
  };
}

template < class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capasity_(0)
{}

template < class T >
topit::Vector< T >::Vector(const Vector< T > &rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = rhs[i];
  }
}

template < class T >
topit::Vector< T >::Vector(Vector< T > &&rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capasity_(rhs.capasity_)
{
  rhs.data_ = nullptr;
}

template < class T >
topit::Vector< T > &topit::Vector< T >::operator=(const Vector< T > &rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template < class T >
topit::Vector< T > &topit::Vector< T >::operator=(Vector< T > &&rhs) noexcept
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template < class T >
T &topit::Vector< T >::operator[](size_t id) noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T >
const T &topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < size_);
  return data_[id];
}
template < class T >
topit::Vector< T >::Vector(size_t k):
  data_(new T[k]),
  size_(k),
  capasity_(k)
{}

template < class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template < class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template < class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template < class T >
size_t topit::Vector< T >::getCapasity() const noexcept
{
  return capasity_;
}

template < class T >
void topit::Vector< T >::swap(Vector< T > &rhs) noexcept
{
  std::swap(rhs.data_, data_);
  std::swap(rhs.size_, size_);
  std::swap(rhs.capasity_, capasity_);
}

template < class T >
void topit::Vector< T >::pushFront(const T &val)
{
  Vector< T > cpy(getSize() + 1);
  cpy[0] = val;
  for (size_t i = 0; i < cpy.getSize(); ++i) {
    cpy[i] = (*this)[i - 1];
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::popFront()
{
  assert(size_ > 1);
  for (size_t i = 0; i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];
  }
  --size_;
}

template < class T >
void topit::Vector< T >::pushBack(const T &val)
{
  if (size_ == capasity_) {
    if (!size_) {
      capasity_ = 1;
    }
    T *tmp = new T[size_ ? size_ * 2 : 2];
    for (size_t i = 0; i < size_; ++i) {
      tmp[i] = (*this)[i];
    }
    capasity_ *= 2;
    std::swap(data_, tmp);
    delete[] tmp;
  }
  data_[size_] = val;
  ++size_;
}

template < class T >
void topit::Vector< T >::popBack()
{
  assert(size_ > 1);
  --size_;
}

template < class T >
T &topit::Vector< T >::at(size_t id)
{
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}
template < class T >
const T &topit::Vector< T >::at(size_t id) const
{
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

template < class T >
void topit::Vector< T >::insert(size_t i, const T &val)
{
  if (i > size_) {
    throw std::out_of_range("index out of range");
  }
  Vector< T > cpy(size_ + 1);
  for (size_t j = 0; j < i; ++j) {
    cpy[j] = (*this)[j];
  }
  cpy[i] = val;
  for (size_t j = i + 1; j < cpy.getSize(); ++j) {
    cpy[j] = (*this)[j - 1];
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::erase(size_t i)
{
  if (i >= size_) {
    throw std::out_of_range("index out of range");
  }
  Vector< T > cpy(size_ - 1);
  for (size_t j = 0; j < i; ++j) {
    cpy[j] = (*this)[j];
  }
  for (size_t j = i + 1; j < size_; ++j) {
    cpy[j - 1] = (*this)[j];
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::insert(size_t i, const Vector< T > &rhs, size_t beg, size_t end)
{
  if (i > size_) {
    throw std::out_of_range("index out of range");
  }
  if (end > rhs.getSize()) {
    throw std::range_error("end index more than size of rhs");
  }
  if (end < beg) {
    throw std::range_error("end less than begin");
  }
  size_t toAdd = end - beg;
  Vector< int > cpy(size_ + toAdd);
  for (size_t j = 0; j < i; ++j) {
    cpy[j] = (*this)[j];
  }
  for (size_t j = i; j < i + toAdd; ++j) {
    cpy[j] = rhs[beg + j - i];
  }
  for (size_t j = i + toAdd; j < cpy.getSize(); ++j) {
    cpy[j] = (*this)[j - toAdd];
  }
  swap(cpy);
}
template < class T >
void topit::Vector< T >::erase(size_t beg, size_t end)
{
  if (!size_) {
    throw std::out_of_range("empty vector");
  }
  if (end > size_) {
    throw std::range_error("end is greater than size");
  }
  if (beg > end) {
    throw std::range_error("begin is greater than end");
  }
  size_t toRemove = end - beg;
  Vector< T > cpy(size_ - toRemove);
  for (size_t i = 0; i < beg; ++i) {
    cpy[i] = (*this)[i];
  }
  for (size_t i = beg; i < cpy.getSize(); ++i) {
    cpy[i] = (*this)[i + toRemove];
  }
  swap(cpy);
}
template < class T >
topit::VCIter< T > topit::Vector< T >::cbegin() const
{
  return VCIter< T >(*this, 0);
}

template < class T >
topit::VIter< T > topit::Vector< T >::begin()
{
  return VIter< T >(*this, 0);
}

template < class T >
topit::VCIter< T > topit::Vector< T >::cend() const
{
  return VCIter< T >(*this, size_);
}

template < class T >
topit::VIter< T > topit::Vector< T >::end()
{
  return VIter< T >(*this, size_);
}
#endif
