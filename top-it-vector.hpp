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
    T &at(size_t id);
    const T &at(size_t id) const;

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
  if (size_ == capasity_) {
    if (!size_) {
      capasity_ = 10;
    }
    T *tmp = new T[size_ ? size_ * 2 : 20];
    for (size_t i = 1; i < size_; ++i) {
      tmp[i] = (*this)[i - 1];
    }
    capasity_ *= 2;
    std::swap(tmp, data_);
    delete[] tmp;
  } else {
    for (size_t i = 0; i < size_; ++i) {
      data_[size_ - i] = data_[size_ - i - 1];
    }
  }
  data_[0] = val;
  ++size_;
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
    return data_[0];
  }
  throw std::range_error("bad id");
}
template < class T >
const T &topit::Vector< T >::at(size_t id) const
{
  if (id < getSize()) {
    return data_[0];
  }
  throw std::range_error("bad id");
}
#endif
