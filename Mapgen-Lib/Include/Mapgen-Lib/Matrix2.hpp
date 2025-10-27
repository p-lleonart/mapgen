#pragma once

#include <cstdlib>
#include <initializer_list>
#include <iostream>

struct MatrixShape2
{
    std::size_t x, y;

    constexpr MatrixShape2();
    constexpr MatrixShape2(std::size_t, std::size_t);
};

/**
 * Generic note about operators: if the two matrices given to an operator aren't compatible for the 
 * requested operation, then the operation won't be executed and the first matrix will be returned.
 * 
 * The operators ``+=``, ``-=``, ``*=``, and ``/=`` must be defined between two ``T`` objects.
 */
template<typename T>
class Matrix2
{
public:
    constexpr Matrix2();
    constexpr Matrix2(std::size_t, std::size_t);
    constexpr Matrix2(const MatrixShape2&);
    constexpr Matrix2(const std::initializer_list<T>&);

    /**
     * The shape of the matrix will be ``size(list) x size(list[0])`` and if there exists a list with:
     * - less elements than ``list[0]``, then it will fill the difference with the default constructor
     * of ``T``.
     * - more elements than ``list[0]``, then it will just omit them.
     */
    constexpr Matrix2(const std::initializer_list<std::initializer_list<T>>&);
    constexpr Matrix2(const Matrix2&);
    constexpr Matrix2(Matrix2&&);
    ~Matrix2();

    [[nodiscard]] constexpr const MatrixShape2& GetShape() const;

    /**
     * Returns ``true`` if the reshape has been executed, ``false`` otherwise (if the new shape is
     * smaller than (or equal to) the previous one).
     */
    constexpr bool Resize(const MatrixShape2&);

    /**
     * Get an item of the matrix with its coordinates.
     */
    [[nodiscard]] constexpr T& operator() (std::size_t, std::size_t);

    constexpr Matrix2<T>& operator=(const Matrix2<T>&);
    constexpr Matrix2<T>& operator+=(const Matrix2<T>&);
    constexpr Matrix2<T>& operator-=(const Matrix2<T>&);
    constexpr Matrix2<T>& operator*=(const Matrix2<T>&);
    constexpr Matrix2<T>& operator*=(T);
    constexpr Matrix2<T>& operator/=(T);

    [[nodiscard]] constexpr Matrix2<T> Transpose() const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix2& M)
    {
        for (std::size_t j = 0; j < M.m_Shape.y; j++)
        {
            os << "| ";
            for (std::size_t i = 0; i < M.m_Shape.x; i++)
            {
                os << M.m_Data[j][i] << " ";
            }
            os << "|\n";
        }
        return os;
    }

private:
    MatrixShape2 m_Shape;
    T** m_Data;

    constexpr void Empty();
};

template<typename T>
[[nodiscard]] constexpr Matrix2<T> operator+(const Matrix2<T>&, const Matrix2<T>&);

template<typename T>
[[nodiscard]] constexpr Matrix2<T> operator-(const Matrix2<T>&, const Matrix2<T>&);

template<typename T>
[[nodiscard]] constexpr Matrix2<T> operator*(const Matrix2<T>&, const Matrix2<T>&);

template<typename T>
[[nodiscard]] constexpr Matrix2<T> operator*(const Matrix2<T>&, T);

template<typename T>
[[nodiscard]] constexpr Matrix2<T> operator*(T, const Matrix2<T>&);

template<typename T>
[[nodiscard]] constexpr Matrix2<T> operator/(const Matrix2<T>&, T);

using Matrix2f = Matrix2<float>;

#include <Mapgen-Lib/Matrix2.inl>
