// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
    for (size_t i = 0; i < sz; i++)
      pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    sz = v.sz;
    pMem = v.pMem;
    v.sz = 0;
    v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this != &v)
    {
      if (sz != v.sz)
      {
        delete[] pMem;
        sz = v.sz;
        pMem = new T[sz];
      }
      for (size_t i = 0; i < sz; i++)
        pMem[i] = v.pMem[i];
    }
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this != &v)
    {
      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
    }
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= sz)
      throw out_of_range("bad index");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz)
      throw out_of_range("bad index");
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return false;
    for (size_t i = 0; i < sz; i++)
      if (pMem[i] != v.pMem[i])
        return false;
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] + val;
    return res;
  }
  TDynamicVector operator-(double val)
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] - (T)val;
    return res;
  }
  TDynamicVector operator*(double val)
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] * (T)val;
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw out_of_range("different size");
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] + v.pMem[i];
    return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw out_of_range("different size");
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] - v.pMem[i];
    return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    T res = T();
    size_t min_sz = sz < v.sz ? sz : v.sz;
    for (size_t i = 0; i < min_sz; i++)
      res = res + pMem[i] * v.pMem[i];
    return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if (sz != m.sz)
      return false;
    for (size_t i = 0; i < sz; i++)
      if (pMem[i] != m.pMem[i])
        return false;
    return true;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
    TDynamicVector<T> res(sz * sz);
    size_t k = 0;
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
      {
        res[k] = pMem[i][j] * val;
        k++;
      }
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (v.size() != sz)
      throw out_of_range("bad size");
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
      T sum = T();
      for (size_t j = 0; j < sz; j++)
        sum = sum + pMem[i][j] * v[j];
      res[i] = sum;
    }
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.sz)
      throw out_of_range("different size");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        res[i][j] = (*this)[i][j] + m[i][j];
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.sz)
      throw out_of_range("different size");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        res[i][j] = (*this)[i][j] - m[i][j];
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz)
      throw out_of_range("different size");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
      {
        T sum = T();
        for (size_t k = 0; k < sz; k++)
          sum = sum + (*this)[i][k] * m[k][j];
        res[i][j] = sum;
      }
    return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      for (size_t j = 0; j < v.sz; j++)
        istr >> v.pMem[i][j];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
    {
      for (size_t j = 0; j < v.sz; j++)
        ostr << v.pMem[i][j] << ' ';
      ostr << endl;
    }
    return ostr;
  }
};

#endif

