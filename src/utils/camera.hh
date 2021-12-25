#pragma once

#include "misc/matrix4.hh"

class Camera
{
public:
    Camera();
    Camera(float x, float y, float z);

    void set_position(misc::Vector3<float> position);
    void set_direction(misc::Vector3<float> direction);
    void set_right(misc::Vector3<float> right);
    void set_up(misc::Vector3<float> up);

    misc::Vector3<float> get_position() const;

    void update_position(float front, float right);

    void update_direction(float horizontal_delta, float vertical_delta);
    misc::Matrix4 compute_vp_matrix() const;
    misc::Matrix4 compute_v_matrix() const;
    misc::Matrix4 compute_p_matrix() const;

private:
    misc::Vector3<float> position_;
    misc::Vector3<float> direction_;
    misc::Vector3<float> right_;
    misc::Vector3<float> up_;

    float horizontal_angle_;
    float vertical_angle_;
};
