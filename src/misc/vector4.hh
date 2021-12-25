#pragma once
#include <ostream>

namespace misc
{
    template <typename T>
    struct Vector4
    {
        Vector4(T x, T y, T z, T w);
        Vector4(const Vector4<T>& copied) = default;
        Vector4() = default;

        T x;
        T y;
        T z;
        T w;

        bool operator==(const Vector4<T>& other) const;
        bool operator!=(const Vector4<T>& other) const;

        Vector4<T> operator+(const Vector4<T>& other) const;
        Vector4<T> operator-(const Vector4<T>& other) const;
        Vector4<T> operator*(const Vector4<T>& other) const;
        Vector4<T> operator*(T val) const;
        Vector4<T> operator/(T val) const;

        T dot(const Vector4<T>& other) const;

        T norm() const;
        Vector4<T> normalize() const;
    };

    template <typename T>
    inline std::ostream& operator<<(std::ostream& out, const Vector4<T>& vector)
    {
        out << '(' << vector.x << ", " << vector.y << ", " << vector.z << ", "
            << vector.w << ')';

        return out;
    }
} // namespace misc

#include "vector4.hxx"
