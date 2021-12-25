#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "scene/scene.hh"

namespace misc
{
    class Window
    {
    public:
        Window(int width, int height);

        ~Window();
        Window(const Window&) = default;
        Window& operator=(const Window&) = default;

        void display(Scene& scene);

        operator GLFWwindow*();

        std::pair<float, float> get_mouse_pos();
        void reset_mouse_pos();

    private:
        int width_;
        int height_;
        GLFWwindow* window_;
    };
} // namespace misc
