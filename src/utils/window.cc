#include "window.hh"

namespace misc
{
    Window::Window(int width, int height)
        : width_(width)
        , height_(height)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        GLFWwindow* window =
            glfwCreateWindow(width_, height_, "Test OpenGL−POGL", NULL, NULL);

        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            window_ = nullptr;
        }

        glfwMakeContextCurrent(window);

        window_ = window;
    }

    Window::~Window()
    {
        glfwDestroyWindow(window_);
    }

    void Window::display(Scene& scene)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.draw();

        glfwSwapBuffers(window_);
    }

    Window::operator GLFWwindow*()
    {
        return window_;
    }

    std::pair<float, float> Window::get_mouse_pos()
    {
        double xpos, ypos;
        glfwGetCursorPos(window_, &xpos, &ypos);
        xpos = static_cast<float>(width_) / 2.0 - xpos;
        ypos = static_cast<float>(height_) / 2.0 - ypos;

        return {xpos, ypos};
    }

    void Window::reset_mouse_pos()
    {
        glfwSetCursorPos(window_, width_ / 2, height_ / 2);
    }
} // namespace misc
