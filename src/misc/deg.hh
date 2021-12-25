#pragma once

#include <cmath>

namespace misc
{
    inline float deg2rad(float deg)
    {
        return (deg / 180.) * M_PI;
    }

    inline float rad2deg(float rad)
    {
        return (rad / M_PI) * 180.;
    }
} // namespace misc
