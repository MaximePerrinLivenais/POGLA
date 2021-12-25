#include "scene_builder.hh"

#include <iostream>
#include "parser/obj_parser.hh"

std::shared_ptr<Scene> build_scene(misc::Options& options)
{
    auto scene = std::make_shared<Scene>();

    scene->get_camera().set_position({-7, -2, 20});

    auto program = Program::make_program(
        options.shaders_dir_path / "bezier_vertex_shader.glsl",
        options.shaders_dir_path / "bezier_tess_control_shader.glsl",
        options.shaders_dir_path / "bezier_tess_evaluation_shader.glsl",
        options.shaders_dir_path / "bezier_fragment_shader.glsl");

    if (!program->is_ready())
    {
        std::cerr << program->get_log() << std::endl;
        return nullptr;
    }

    {
        auto points = std::vector<float>({-1.0, 0.5, 1.0,
                                            -0.5, 0.5, -1.0,
                                            0.5, 0.5, -1.0,
                                            1.0, 0.5, -1.0,
                                            -1.0, 0.0, -0.5,
                                            -0.5, 0.0, -0.5,
                                            0.5, 0.0, -0.5,
                                            1.0, 0.0, -0.5,
                                            -1.0, 0.0, 0.5,
                                            -0.5, 0.0, 0.5,
                                            0.5, 0.0, 0.5,
                                            1.0, 0.0, 0.5,
                                            -1.0, -0.5, 1.0,
                                            -0.5, 0.3, 1.0,
                                            0.5, 0.3,  1.0,
                                            1.0, 0.3,  1.0});

        auto fun = [](){ glPatchParameteri(GL_PATCH_VERTICES, 16); glDrawArrays(GL_PATCHES, 0, 16); };

        auto object = Object::build_new_object(points, 3, program, fun);

        scene->add_object(object);
    }

    return scene;
}
