#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "misc/deg.hh"
#include "parser/option_parser.hh"
#include "parser/obj_parser.hh"
#include "scene/scene.hh"
#include "scene/scene_builder.hh"
#include "utils/object.hh"
#include "utils/program.hh"
#include "utils/texture.hh"
#include "utils/window.hh"

void init_gl(void)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthRange(0.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.07, 0.07, 0.35, 1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
}

bool initGlew()
{
    glewExperimental = GL_TRUE;
    return (glewInit() == GLEW_OK);
}

void set_uniform(GLuint program_id)
{
    GLuint light_position_id =
        glGetUniformLocation(program_id, "light_position");

    float light_pos[3] = {2, 0, 3};

    glUniform3fv(light_position_id, 1, light_pos);
}

int main(int argc, char** argv)
{
    misc::Options options(argc, argv);

    auto window = misc::Window(options.screen_width, options.screen_height);
    init_gl();
    initGlew();

    auto scene = build_scene(options);

    // main_loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        scene->update(window);

        // render
        window.display(*scene);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
