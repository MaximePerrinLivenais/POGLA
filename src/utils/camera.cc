#include "camera.hh"
#include "misc/deg.hh"
#include "misc/program_parameters.hh"
#include <iostream>

Camera::Camera()
    : position_{0, 0, 0}
    , direction_{0, 0, 0}
    , right_{1, 0, 0}
    , up_{0, 1, 0}
    , horizontal_angle_(misc::deg2rad(180))
    , vertical_angle_(0)
{}

Camera::Camera(float x, float y, float z)
    : position_{x, y, z}
    , direction_{0, 0, 0}
    , right_{1, 0, 0}
    , up_{0, 1, 0}
    , horizontal_angle_(misc::deg2rad(180))
    , vertical_angle_(0)
{}

void Camera::set_position(misc::Vector3<float> position)
{
    position_ = position;
}

void Camera::set_direction(misc::Vector3<float> direction)
{
    direction_ = direction;
}

void Camera::set_right(misc::Vector3<float> right)
{
    right_ = right;
}

void Camera::set_up(misc::Vector3<float> up)
{
    up_ = up;
}

misc::Vector3<float> Camera::get_position() const
{
    return position_;
}

void Camera::update_position(float front, float right)
{
    auto normalized_dir = direction_;
    normalized_dir.y = 0;
    normalized_dir = normalized_dir.normalize();

    auto normalized_right = right_;
    normalized_right.y = 0;
    normalized_right = normalized_right.normalize();

    position_ += normalized_dir * front;
    position_ += normalized_right * right;
}

void Camera::update_direction(float horizontal_delta, float vertical_delta)
{
    horizontal_angle_ += horizontal_delta;
    vertical_angle_ += vertical_delta;

    direction_.x = std::cos(vertical_angle_) * std::sin(horizontal_angle_);
    direction_.y = std::sin(vertical_angle_);
    direction_.z = std::cos(vertical_angle_) * std::cos(horizontal_angle_);

    right_ = {std::sin(horizontal_angle_ - 3.14f / 2.0f), 0,
              std::cos(horizontal_angle_ - 3.14f / 2.0f)};

    up_ = right_.cross(direction_);
}

misc::Matrix4 Camera::compute_vp_matrix() const
{
    auto abs_dir = direction_ + position_;

    auto vp = misc::Matrix4::identity();

    misc::look_at(vp, {position_.x, position_.y, position_.z},
                  {abs_dir.x, abs_dir.y, abs_dir.z}, {up_.x, up_.y, up_.z});

    misc::frustum(vp, -1, 1, -1, 1, z_dist_min, z_dist_max);

    return vp;
}

misc::Matrix4 Camera::compute_v_matrix() const
{
    auto abs_dir = direction_ + position_;

    auto v = misc::Matrix4::identity();

    misc::look_at(v, {position_.x, position_.y, position_.z},
                  {abs_dir.x, abs_dir.y, abs_dir.z}, {up_.x, up_.y, up_.z});

    return v;
}

misc::Matrix4 Camera::compute_p_matrix() const
{
    auto p = misc::Matrix4::identity();

    misc::frustum(p, -1, 1, -1, 1, z_dist_min, z_dist_max);

    return p;
}
