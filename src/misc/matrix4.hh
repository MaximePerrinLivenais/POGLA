#pragma once

#include <array>
#include <ostream>
#include "vector3.hh"
#include "vector4.hh"

namespace misc
{
    class Matrix4
    {
    public:
        Matrix4();

        void operator*=(const Matrix4& rhs);
        Vector4<float> operator*(const Vector4<float>& rhs);

        static Matrix4 identity();

        void set(int i, int j, float val);
        float get(int i, int j) const;

        void translate(float x, float y, float z);
        void rotation(float x, float y, float z);
        void scale(float x, float y, float z);

        Matrix4 transpose() const;

        void dump(std::ostream& ostr) const;

        float* data();

    private:
        std::array<float, 16> matrix_;
    };

    std::ostream& operator<<(std::ostream& ostr, const Matrix4& m);

    void frustum(Matrix4& mat, float left, float right, float bottom, float top,
                 float z_near, float z_far);

    void look_at(Matrix4& mat, Vector3<float> eye, Vector3<float> center,
                 Vector3<float> up);

} // namespace misc

#include "matrix4.hxx"
