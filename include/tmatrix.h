// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

#define STR1(x)  #x
#define STR(x)  STR1(x)

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
        {
            throw out_of_range("Vector size should be greater than zero");
        }

        if (sz > MAX_VECTOR_SIZE)
        {
            throw out_of_range("Vector size should be less than " STR(MAX_VECTOR_SIZE));
        }

        pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
    }

    TDynamicVector(const T* arr, size_t s) : sz(s)
    {
        if (arr == nullptr)
        {
            throw invalid_argument("TDynamicVector ctor requires non-nullptr arg");
        }

        if (sz == 0)
        {
            throw out_of_range("Vector size should be greater than zero");
        }

        if (sz > MAX_VECTOR_SIZE)
        {
            throw out_of_range("Vector size should be less than " STR(MAX_VECTOR_SIZE));
        }

        pMem = new T[sz]();
        copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz]();

        copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = v.pMem;
        sz = v.sz;

        v.pMem = nullptr;
        v.sz = 0;
    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            T* tmp = new T[v.sz]();
            sz = v.sz;
            delete[] pMem;
            pMem = tmp;
        }

        copy(v.pMem, v.pMem + sz, pMem);

        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(pMem, v.pMem);
        swap(sz, v.sz);

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
        {
            throw out_of_range("Index should be less than sz of TDynamicVector");
        }

        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if (ind >= sz)
        {
            throw out_of_range("Index should be less than sz of TDynamicVector");
        }

        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
        {
            return false;
        }

        for (size_t i = 0; i < sz; ++i)
        {
            if (pMem[i] != v.pMem[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !operator==(v);
    }

    // скалярные операции
    TDynamicVector operator+(const T& val)
    {
        TDynamicVector<T> res(*this);

        for (size_t i = 0; i < sz; ++i)
        {
            res.pMem[i] += val;
        }

        return res;
    }

    TDynamicVector operator-(const T& val)
    {
        TDynamicVector<T> res(*this);

        for (size_t i = 0; i < sz; ++i)
        {
            res.pMem[i] -= val;
        }

        return res;
    }

    TDynamicVector operator*(T val)
    {
        TDynamicVector<T> res(*this);

        for (size_t i = 0; i < sz; ++i)
        {
            res.pMem[i] *= val;
        }

        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw logic_error("Vector sizes should be equal");
        }

        TDynamicVector<T> res(*this);
        for (size_t i = 0; i < sz; ++i)
        {
            res[i] += v[i];
        }

        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw logic_error("Vector sizes should be equal");
        }

        TDynamicVector<T> res(*this);
        for (size_t i = 0; i < sz; ++i)
        {
            res[i] -= v[i];
        }

        return res;
    }

    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw logic_error("Vector sizes should be equal");
        }

        T res{};
        for (size_t i = 0; i < sz; ++i)
        {
            res += pMem[i] * v[i];
        }

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
private:
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz == 0)
        {
            throw out_of_range("Matrix size should be greater than zero");
        }

        if (sz > MAX_MATRIX_SIZE)
        {
            throw out_of_range("Matrix size should be less than " STR(MAX_MATRIX_SIZE));
        }

        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::size;

    T& at(size_t i, size_t j)
    {
        if (i >= sz || j >= sz)
        {
            throw logic_error("Indices should be less than matrix size");
        }

        return pMem[i][j];
    }

    const T& at(size_t i, size_t j) const
    {
        if (i >= sz || j >= sz)
        {
            throw logic_error("Indices should be less than matrix size");
        }

        return pMem[i][j];
    }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator!=(m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix res(*this);

        for (size_t i = 0; i < sz; ++i)
        {
            for (size_t j = 0; j < sz; ++j)
            {
                res[i][j] *= val;
            }
        }

        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz)
        {
            throw logic_error("Matrix and vector sizes should be equal");
        }

        TDynamicVector<T> res(sz);

        for (size_t i = 0; i < sz; ++i)
        {
            for (size_t j = 0; j < sz; ++j)
            {
                res[i] += pMem[i][j] * v[j];
            }
        }

        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw logic_error("Matrix sizes should be equal");
        }

        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; ++i)
        {
            for (size_t j = 0; j < sz; ++j)
            {
                res[i][j] += m[i][j];
            }
        }

        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw logic_error("Matrix sizes should be equal");
        }

        TDynamicMatrix<T> res(*this);
        for (size_t i = 0; i < sz; ++i)
        {
            for (size_t j = 0; j < sz; ++j)
            {
                res[i][j] -= m[i][j];
            }
        }

        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw logic_error("Matrix sizes should be equal");
        }

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i)
        {
            for (size_t k = 0; k < sz; ++k)
            {
                for (size_t j = 0; j < sz; ++j)
                {
                    res[i][j] += pMem[i][k] * m[k][j];
                }
            }
        }

        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.size(); ++i)
        {
            istr >> v[i];
        }

        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.size(); ++i)
        {
            ostr << v[i] << '\n';
        }

        return ostr;
    }
};

#endif
