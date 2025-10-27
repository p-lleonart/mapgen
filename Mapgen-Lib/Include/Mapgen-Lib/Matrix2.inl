#include <Mapgen-Lib/Matrix2.hpp>

constexpr MatrixShape2::MatrixShape2() : x(0), y(0)
{
}

constexpr MatrixShape2::MatrixShape2(std::size_t n, std::size_t p) : x(n), y(p)
{
}

template<typename T>
constexpr Matrix2<T>::Matrix2() : m_Data(nullptr), m_Shape(0, 0)
{
}

template<typename T>
constexpr Matrix2<T>::Matrix2(std::size_t n, std::size_t p) : Matrix2(MatrixShape2(n, p))
{
}

template<typename T>
constexpr Matrix2<T>::Matrix2(const MatrixShape2& shape)
{
    m_Shape = shape;
    m_Data = new T*[shape.y];
    for (std::size_t j = 0; j < shape.y; j++)
    {
        m_Data[j] = new T[shape.x];
        for (std::size_t i = 0; i < shape.x; i++)
            m_Data[j][i] = T();
    }
}

template<typename T>
constexpr Matrix2<T>::Matrix2(const std::initializer_list<T>& list) : Matrix2(list.size(), 1)
{
    std::size_t i = 0;
    for (const T& elem : list)
    {
        m_Data[0][i] = elem;
        i++;
    }
}

template<typename T>
constexpr Matrix2<T>::Matrix2(const std::initializer_list<std::initializer_list<T>>& list)
{
    m_Shape = MatrixShape2(list.begin()->size(), list.size());
    m_Data = new T*[m_Shape.y];

    std::size_t j = 0, i = 0;
    for (const std::initializer_list<T>& vect : list)
    {
        // In this case, we will forget the values of the list after ``m_Shape.x``, or we will fill
        // the rest with zeros, depending on the case.
        if (vect.size() != m_Shape.x)
        {
            std::cerr << "[Mapgen-Lib] warning: the line " << j << "'s size (" << vect.size()
                << ") is not equal to the expected one (" << m_Shape.x << ").\n";
        }
        m_Data[j] = new T[m_Shape.x];
        for (const T& elem : vect)
        {
            if (i > vect.size()) m_Data[j][i] = T();
            else m_Data[j][i] = elem;
            i++;
        }
        i = 0;
        j++;
    }
}

template<typename T>
constexpr Matrix2<T>::Matrix2(const Matrix2<T>& other)
{
    m_Shape = other.m_Shape;
    m_Data = new T*[m_Shape.y];

    for (std::size_t j = 0; j < m_Shape.y; j++)
    {
        m_Data[j] = new T[m_Shape.x];
        for(std::size_t i = 0; i < m_Shape.x; i++)
            m_Data[j][i] = other.m_Data[j][i];
    }
}

template<typename T>
constexpr Matrix2<T>::Matrix2(Matrix2&& other)
{
    m_Shape = other.m_Shape;
    m_Data = other.m_Data;
    
    other.m_Shape = MatrixShape2(0, 0);
    other.m_Data = nullptr;
}

template<typename T>
Matrix2<T>::~Matrix2()
{
    Empty();
}

template<typename T>
constexpr void Matrix2<T>::Empty()
{
    for (std::size_t j = 0; j < m_Shape.y; j++)
        delete[] m_Data[j];
    delete[] m_Data;
    m_Shape = MatrixShape2(0, 0);
}

template<typename T>
constexpr const MatrixShape2& Matrix2<T>::GetShape() const
{
    return m_Shape;
}

template<typename T>
constexpr bool Matrix2<T>::Resize(const MatrixShape2& shape)
{
    if (m_Shape.x >= shape.x || m_Shape.y >= shape.y) return false;

    Matrix2<T> M = Matrix2<T>(shape);
    for (std::size_t j = 0; j < shape.y; j++)
        for (std::size_t i = 0; i < shape.x; i++)
        {
            if (j >= m_Shape.y || i >= m_Shape.x) M.m_Data[j][i] = T();
            else M.m_Data[j][i] = m_Data[j][i];
        }
    *this = M;
    return true;
}

template<typename T>
constexpr T& Matrix2<T>::operator() (std::size_t i, std::size_t j)
{
    return m_Data[j][i];
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& other)
{
    if (this == &other) return *this;

    Empty();
    m_Shape = other.m_Shape;
    m_Data = new T*[m_Shape.y];

    for (std::size_t j = 0; j < m_Shape.y; j++)
    {
        m_Data[j] = new T[m_Shape.x];
        for (std::size_t i = 0; i < m_Shape.x; i++)
            m_Data[j][i] = other.m_Data[j][i];
    }

    return *this;
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator=(Matrix2<T>&& other)
{
    if (this == &other) return *this;

    Empty();
    m_Shape = other.m_Shape;
    m_Data = other.m_Data;
    
    other.m_Shape = MatrixShape2(0, 0);
    other.m_Data = nullptr;
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator+=(const Matrix2<T>& other)
{
    if (m_Shape.x != other.m_Shape.x || m_Shape.y != other.m_Shape.y)
    {
        std::cerr << "[Mapgen-Lib] warning: the two matrices don't have the same shapes.\n";
        return *this;
    }

    for(std::size_t j = 0; j < m_Shape.y; j++)
        for(std::size_t i = 0; i < m_Shape.x; i++)
            m_Data[j][i] += other.m_Data[j][i];
    
    return *this;
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator-=(const Matrix2<T>& other)
{
    if (m_Shape.x != other.m_Shape.x || m_Shape.y != other.m_Shape.y)
    {
        std::cerr << "[Mapgen-Lib] warning: the two matrices don't have the same shapes.\n";
        return *this;
    }

    for(std::size_t j = 0; j < m_Shape.y; j++)
        for(std::size_t i = 0; i < m_Shape.x; i++)
            m_Data[j][i] -= other.m_Data[j][i];
    
    return *this;
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T>& other)
{
    if (m_Shape.x != other.m_Shape.y)
    {
        std::cerr << "[Mapgen-Lib] warning: the two matrices don't have the correct shapes.\n";
        return *this;
    }

    Matrix2<T> M(MatrixShape2(m_Shape.y, other.m_Shape.x));

    for(std::size_t j = 0; j < M.m_Shape.y; j++)
        for(std::size_t i = 0; i < M.m_Shape.x; i++)
            for(std::size_t k = 0; k < m_Shape.x; k++)
                M.m_Data[j][i] += (m_Data[j][k] * other.m_Data[k][i]);

    *this = M;

    return *this;
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator*=(T val)
{
    for(std::size_t j = 0; j < m_Shape.y; j++)
        for(std::size_t i = 0; i < m_Shape.x; i++)
            m_Data[j][i] *= val;
    
    return *this;
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator/=(T val)
{
    for(std::size_t j = 0; j < m_Shape.y; j++)
        for(std::size_t i = 0; i < m_Shape.x; i++)
            m_Data[j][i] /= val;
    
    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::Transpose() const
{
    Matrix2<T> M(MatrixShape2(m_Shape.y, m_Shape.x));

    for(std::size_t j = 0; j < m_Shape.y; j++)
        for(std::size_t i = 0; i < m_Shape.x; i++)
            M.m_Data[i][j] = m_Data[j][i];

    return M;
}

template<typename T>
constexpr Matrix2<T> operator+(const Matrix2<T>& A, const Matrix2<T>& B)
{
    Matrix2<T> temp = A;
    temp += B;
    return temp;
}

template<typename T>
constexpr Matrix2<T> operator-(const Matrix2<T>& A, const Matrix2<T>& B)
{
    Matrix2<T> temp = A;
    temp -= B;
    return temp;
}

template<typename T>
constexpr Matrix2<T> operator*(const Matrix2<T>& A, const Matrix2<T>& B)
{
    Matrix2<T> temp = A;
    temp *= B;
    return temp;
}

template<typename T>
constexpr Matrix2<T> operator*(const Matrix2<T>& A, T scalar)
{
    Matrix2<T> temp = A;
    temp *= scalar;
    return temp;
}

template<typename T>
constexpr Matrix2<T> operator*(T scalar, const Matrix2<T>& A)
{
    Matrix2<T> temp = A;
    temp *= scalar;
    return temp;
}

template<typename T>
constexpr Matrix2<T> operator/(const Matrix2<T>& A, T scalar)
{
    Matrix2<T> temp = A;
    temp /= scalar;
    return temp;
}
