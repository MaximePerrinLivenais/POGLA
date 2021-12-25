#pragma once

#include "misc/matrix4.hh"
#include "misc/vector3.hh"

struct Scene_data
{
    const misc::Matrix4& vp_matrix;
    const misc::Vector3<float>& camera_position;
};
