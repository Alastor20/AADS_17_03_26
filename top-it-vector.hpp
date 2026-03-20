#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cassert>
#include <cstddef>
#include <utility>

namespace topit
{
  template < class T >
  class Vector
  {
  public:
    Vector();
    Vector(const Vector< T > &);
    Vector< T > &operator=(const Vector< T > &);
    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;
    ~Vector();
    bool isEmpty() const noexcept;
    void pushBack(const T &) {};
    size_t size() const noexcept;
    void swap(Vector< T > &rhs) noexcept;
    void pushFront(const T &);

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
  Vector(rhs.size())
{
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = rhs[i];
  }
}

template < class T >
T &topit::Vector< T >::operator[](size_t id) noexcept
{
  assert(id < size());
  return data_[0];
}

template < class T >
const T &topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < size_);
  return data_[0];
}
template < class T >
topit::Vector< T >::Vector(size_t k):
  data_(new T[k]),
  size_(k),
  capasity_(k)
{}

template < class T >
topit::Vector< T > &topit::Vector< T >::operator=(const Vector< T > &rhs)
{
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}
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
size_t topit::Vector< T >::size() const noexcept
{
  return size_;
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
  Vector< T > cpy(val.size() + 1);
  cpy[0] = val;
  for (size_t i = 0; i < cpy.size(); ++i) {
    cpy[i] = (*this)[i - 1];
  }
  swap(cpy);
}

#endif
