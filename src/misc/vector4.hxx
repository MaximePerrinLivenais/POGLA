#pragma once
#include "vector4.hh"
#include <cmath>

namespace misc
{
    template <typename T>
    inline Vector4<T>::Vector4(T x, T y, T z, T w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {}

    template <typename T>
    inline bool Vector4<T>::operator==(const Vector4<T>& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    template <typename T>
    inline bool Vector4<T>::operator!=(const Vector4<T>& other) const
    {
        return !((*this) == other);
    }

    template <typename T>
    inline Vector4<T> Vector4<T>::operator*(T other) const
    {
        return Vector4<T>{static_cast<T>(x * other), static_cast<T>(y * other),
                          static_cast<T>(z * other), static_cast<T>(w * other)};
    }

    template <typename T>
    inline Vector4<T> Vector4<T>::operator/(T other) const
    {
        return Vector4<T>{static_cast<T>(x / other), static_cast<T>(y / other),
                          static_cast<T>(z / other), static_cast<T>(w / other)};
    }

    template <typename T>
    inline Vector4<T> Vector4<T>::operator+(const Vector4<T>& other) const
    {
        return Vector4<T>{x + other.x, y + other.y, z + other.z, w + other.w};
    }

    template <typename T>
    inline Vector4<T> Vector4<T>::operator-(const Vector4<T>& other) const
    {
        return Vector4<T>{x - other.x, y - other.y, z - other.z, w - other.w};
    }

    template <typename T>
    inline Vector4<T> Vector4<T>::operator*(const Vector4<T>& other) const
    {
        return Vector4<T>{x * other.x, y * other.y, z * other.z, w * other.w};
    }

    template <typename T>
    inline T Vector4<T>::dot(const Vector4<T>& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    template <typename T>
    T Vector4<T>::norm() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    template <typename T>
    Vector4<T> Vector4<T>::normalize() const
    {
        auto n = norm();
        if (n)
            return (*this) / n;
        return Vector4<T>{0, 0, 0, 0};
    }
} // namespace misc
