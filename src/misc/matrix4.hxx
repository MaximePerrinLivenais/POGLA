#pragma once

#include "matrix4.hh"

namespace misc
{
    inline void Matrix4::set(int i, int j, float val)
    {
        matrix_[i * 4 + j] = val;
    }

    inline float Matrix4::get(int i, int j) const
    {
        return matrix_[i * 4 + j];
    }
} // namespace misc
