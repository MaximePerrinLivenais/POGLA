#include "scene.hh"

#include "scene_data.hh"
#include "misc/program_parameters.hh"
#include "utils/window.hh"

Scene::Scene()
{
    time_ = glfwGetTime();
}

void Scene::update(misc::Window& window)
{
    double cur_time = glfwGetTime();
    float delta_time = cur_time - time_;
    time_ = cur_time;

    float front = 0;
    float right = 0;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        front += 1;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        front -= 1;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        right += 1;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        right -= 1;

    front *= delta_time * move_speed;
    right *= delta_time * move_speed;
    update_camera_position(front, right);

    auto [xpos, ypos] = window.get_mouse_pos();
    window.reset_mouse_pos();

    float horizontalAngle = delta_time * mouse_speed * xpos;

    float verticalAngle = delta_time * mouse_speed * ypos;

    update_camera_direction(horizontalAngle, verticalAngle);

    //skybox_->set_location(camera_.get_position());
}

void Scene::draw()
{
    auto vp = compute_vp_matrix();
    auto cam_pos = get_camera().get_position();

    Scene_data data{vp, cam_pos};

    //skybox_->draw(data);
    //ground_->draw(data);

    for (auto obj : objects_)
        obj->draw(data);
}

void Scene::add_object(std::shared_ptr<Object> object)
{
    objects_.push_back(object);
}

misc::Matrix4 Scene::compute_vp_matrix() const
{
    return camera_.compute_vp_matrix();
}

misc::Matrix4 Scene::compute_v_matrix() const
{
    return camera_.compute_v_matrix();
}

misc::Matrix4 Scene::compute_p_matrix() const
{
    return camera_.compute_p_matrix();
}

void Scene::update_camera_position(float front, float right)
{
    camera_.update_position(front, right);
}

void Scene::update_camera_direction(float horizontal_delta,
                                    float vertical_delta)
{
    camera_.update_direction(horizontal_delta, vertical_delta);
}

Camera& Scene::get_camera()
{
    return camera_;
}

void Scene::set_skybox(std::shared_ptr<Object> skybox)
{
    skybox_ = skybox;
}

void Scene::set_ground(std::shared_ptr<Object> ground)
{
    ground_ = ground;
}
