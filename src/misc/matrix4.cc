#include "matrix4.hh"

#include <cmath>
#include <iostream>

namespace misc
{
    Matrix4::Matrix4()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                set(i, j, 0);
    }

    void Matrix4::operator*=(const Matrix4& rhs)
    {
        Matrix4 res;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float s = 0;
                for (int k = 0; k < 4; k++)
                {
                    s += get(i, k) * rhs.get(k, j);
                }
                res.set(i, j, s);
            }
        }

        matrix_ = res.matrix_;
    }

    Vector4<float> Matrix4::operator*(const Vector4<float>& rhs)
    {
        Vector4<float> res;

        res.x = get(0, 0) * rhs.x + get(0, 1) * rhs.y + get(0, 2) * rhs.z
            + get(0, 3) * rhs.w;

        res.y = get(1, 0) * rhs.x + get(1, 1) * rhs.y + get(1, 2) * rhs.z
            + get(1, 3) * rhs.w;

        res.z = get(2, 0) * rhs.x + get(2, 1) * rhs.y + get(2, 2) * rhs.z
            + get(2, 3) * rhs.w;

        res.w = get(3, 0) * rhs.x + get(3, 1) * rhs.y + get(3, 2) * rhs.z
            + get(3, 3) * rhs.w;

        return res;
    }

    Matrix4 Matrix4::identity()
    {
        Matrix4 res;
        res.set(0, 0, 1);
        res.set(1, 1, 1);
        res.set(2, 2, 1);
        res.set(3, 3, 1);

        return res;
    }

    Matrix4 Matrix4::transpose() const
    {
        Matrix4 res;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                res.set(i, j, get(j, i));

        return res;
    }

    void Matrix4::translate(float x, float y, float z)
    {
        Matrix4 M = identity();
        M.set(0, 3, x);
        M.set(1, 3, y);
        M.set(2, 3, z);

        *this *= M;
    }

    void Matrix4::scale(float x, float y, float z)
    {
        Matrix4 M = identity();
        M.set(0, 0, x);
        M.set(1, 1, y);
        M.set(2, 2, z);

        *this *= M;
    }

    void Matrix4::rotation(float x, float y, float z)
    {
        Matrix4 M = identity();

        const auto cos_x = std::cos(x);
        const auto sin_x = std::sin(x);
        const auto cos_y = std::cos(y);
        const auto sin_y = std::sin(y);
        const auto cos_z = std::cos(z);
        const auto sin_z = std::sin(z);

        M.set(0, 0, cos_y * cos_z);
        M.set(0, 1, cos_x * sin_z + cos_z * sin_x * sin_y);
        M.set(0, 2, sin_x * sin_z - cos_x * cos_z * sin_y);

        M.set(1, 0, -cos_y * sin_z);
        M.set(1, 1, cos_x * cos_z - sin_x * sin_y * sin_z);
        M.set(1, 2, cos_z * sin_x + cos_x * sin_y * sin_z);

        M.set(2, 0, sin_y);
        M.set(2, 1, -cos_y * sin_x);
        M.set(2, 2, cos_x * cos_y);

        *this *= M;
    }

    void Matrix4::dump(std::ostream& ostr) const
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
                ostr << get(i, j) << " ";
            ostr << get(i, 3) << "\n";
        }
    }

    float* Matrix4::data()
    {
        return matrix_.data();
    }

    std::ostream& operator<<(std::ostream& ostr, const Matrix4& m)
    {
        m.dump(ostr);
        return ostr;
    }

    void frustum(Matrix4& mat, float left, float right, float bottom, float top,
                 float z_near, float z_far)
    {
        Matrix4 frustum;

        frustum.set(0, 0, 2.0f * z_near / (right - left));
        frustum.set(0, 2, (right + left) / (right - left));

        frustum.set(1, 1, 2.0f * z_near / (top - bottom));
        frustum.set(1, 2, (top + bottom) / (top - bottom));

        frustum.set(2, 2, -(z_far + z_near) / (z_far - z_near));

        frustum.set(2, 3, -(2.0f * z_far * z_near) / (z_far - z_near));
        frustum.set(3, 2, -1.0f);

        frustum *= mat;
        mat = frustum;
    }

    void look_at(Matrix4& mat, Vector3<float> eye, Vector3<float> center,
                 Vector3<float> up)
    {
        auto f = (center - eye).normalize();
        auto u = up.normalize();
        auto s = f.cross(u);
        u = s.normalize().cross(f);

        Matrix4 M;
        M.set(0, 0, s.x);
        M.set(0, 1, s.y);
        M.set(0, 2, s.z);

        M.set(1, 0, u.x);
        M.set(1, 1, u.y);
        M.set(1, 2, u.z);

        M.set(2, 0, -f.x);
        M.set(2, 1, -f.y);
        M.set(2, 2, -f.z);

        M.set(3, 3, 1);

        M *= mat;
        mat = M;

        mat.translate(-eye.x, -eye.y, -eye.z);
    }

} // namespace misc
