#pragma once
#include <ostream>

namespace misc
{
    template <typename T>
    struct Vector3
    {
        Vector3(T x, T y, T z);
        Vector3(const Vector3<T>& copied) = default;
        Vector3() = default;

        T x;
        T y;
        T z;

        bool operator==(const Vector3<T>& other) const;
        bool operator!=(const Vector3<T>& other) const;

        Vector3<T> operator+(const Vector3<T>& other) const;
        Vector3<T> operator-(const Vector3<T>& other) const;
        Vector3<T> operator*(const Vector3<T>& other) const;
        Vector3<T> operator*(T val) const;
        Vector3<T> operator/(T val) const;

        void operator+=(const Vector3<T>& other);

        T dot(const Vector3<T>& other) const;
        Vector3<T> cross(const Vector3<T>& other) const;

        T norm() const;
        Vector3<T> normalize() const;
    };

    template <typename T>
    inline std::ostream& operator<<(std::ostream& out, const Vector3<T>& vector)
    {
        out << '(' << vector.x << ',' << vector.y << ',' << vector.z << ')';

        return out;
    }
} // namespace misc

#include "vector3.hxx"
