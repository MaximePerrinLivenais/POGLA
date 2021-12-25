#include <memory>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utils/camera.hh"
#include "utils/object.hh"
#include "utils/vao.hh"

namespace misc
{
    class Window;
}

#pragma once

class Scene
{
public:
    using iterator = std::vector<std::shared_ptr<Object>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Object>>::const_iterator;

    Scene();

    void update(misc::Window& window);
    void draw();

    void add_object(std::shared_ptr<Object> object);

    misc::Matrix4 compute_vp_matrix() const;
    misc::Matrix4 compute_v_matrix() const;
    misc::Matrix4 compute_p_matrix() const;

    void update_camera_position(float front, float right);
    void update_camera_direction(float horizontal_delta, float vertical_delta);

    Camera& get_camera();

    void set_skybox(std::shared_ptr<Object> skybox);
    void set_ground(std::shared_ptr<Object> ground);

private:
    Camera camera_;

    std::vector<std::shared_ptr<Object>> objects_;

    std::shared_ptr<Object> ground_;
    std::shared_ptr<Object> skybox_;

    double time_;
};

using shared_scene = std::shared_ptr<Scene>;
