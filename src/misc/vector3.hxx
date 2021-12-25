#pragma once
#include "vector3.hh"
#include <cmath>

namespace misc
{
    template <typename T>
    inline Vector3<T>::Vector3(T x, T y, T z)
        : x(x)
        , y(y)
        , z(z)
    {}

    template <typename T>
    inline bool Vector3<T>::operator==(const Vector3<T>& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    template <typename T>
    inline bool Vector3<T>::operator!=(const Vector3<T>& other) const
    {
        return !((*this) == other);
    }

    template <typename T>
    inline Vector3<T> Vector3<T>::operator*(T other) const
    {
        return Vector3<T>{static_cast<T>(x * other), static_cast<T>(y * other),
                          static_cast<T>(z * other)};
    }

    template <typename T>
    inline Vector3<T> Vector3<T>::operator/(T other) const
    {
        return Vector3<T>{static_cast<T>(x / other), static_cast<T>(y / other),
                          static_cast<T>(z / other)};
    }

    template <typename T>
    inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const
    {
        return Vector3<T>{x + other.x, y + other.y, z + other.z};
    }

    template <typename T>
    inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const
    {
        return Vector3<T>{x - other.x, y - other.y, z - other.z};
    }

    template <typename T>
    inline Vector3<T> Vector3<T>::operator*(const Vector3<T>& other) const
    {
        return Vector3<T>{x * other.x, y * other.y, z * other.z};
    }

    template <typename T>
    inline void Vector3<T>::operator+=(const Vector3<T>& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    template <typename T>
    inline T Vector3<T>::dot(const Vector3<T>& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    template <typename T>
    Vector3<T> Vector3<T>::cross(const Vector3<T>& other) const
    {
        return Vector3<T>{
            (y * other.z) - (z * other.y),
            (z * other.x) - (x * other.z),
            (x * other.y) - (y * other.x),
        };
    }

    template <typename T>
    T Vector3<T>::norm() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    template <typename T>
    Vector3<T> Vector3<T>::normalize() const
    {
        auto n = norm();
        if (n)
            return (*this) / n;
        return Vector3<T>{0, 0, 0};
    }
} // namespace misc
