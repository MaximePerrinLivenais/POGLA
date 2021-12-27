#include "scene_builder.hh"

#include <iostream>

#include "parser/obj_parser.hh"

std::shared_ptr<Scene> build_scene(misc::Options& options)
{
    auto scene = std::make_shared<Scene>();

    scene->get_camera().set_position({-7, -2, 20});

    auto bezier_program = Program::make_program(
        options.shaders_dir_path / "bezier_vertex_shader.glsl",
        options.shaders_dir_path / "bezier_tess_control_shader.glsl",
        options.shaders_dir_path / "bezier_tess_evaluation_shader.glsl",
        options.shaders_dir_path / "bezier_geometry_shader.glsl",
        options.shaders_dir_path / "bezier_fragment_shader.glsl");

    if (!bezier_program->is_ready())
    {
        std::cerr << bezier_program->get_log() << std::endl;
        return nullptr;
    }

    auto bezier_normals_program = Program::make_program(
        options.shaders_dir_path / "bezier_vertex_shader.glsl",
        options.shaders_dir_path / "bezier_tess_control_shader.glsl",
        options.shaders_dir_path / "bezier_tess_evaluation_shader.glsl",
        options.shaders_dir_path / "bezier_normals_geometry_shader.glsl",
        options.shaders_dir_path / "bezier_fragment_shader.glsl");

    if (!bezier_normals_program->is_ready())
    {
        std::cerr << bezier_normals_program->get_log() << std::endl;
        return nullptr;
    }

    {
        auto color = misc::Vector3<float>(0., 1., 1.);

        auto points = std::vector<float>({-1.0, 0.5,  1.0, //
                                          -0.5, 0.5,  -1.0, //
                                          0.5,  0.5,  -1.0, //
                                          1.0,  0.5,  -1.0, //
                                          -1.0, 0.0,  -0.5, //
                                          -0.5, 0.0,  -0.5, //
                                          0.5,  0.0,  -0.5, //
                                          1.0,  0.0,  -0.5, //
                                          -1.0, 0.0,  0.5, //
                                          -0.5, 0.0,  0.5, //
                                          0.5,  0.0,  0.5, //
                                          1.0,  0.0,  0.5, //
                                          -1.0, -0.5, 1.0, //
                                          -0.5, 0.3,  1.0, //
                                          0.5,  0.3,  1.0, //
                                          1.0,  0.3,  1.0});

        auto fun = []() {
            glPatchParameteri(GL_PATCH_VERTICES, 16);
            glDrawArrays(GL_PATCHES, 0, 16);
        };

        auto programs = {bezier_program, bezier_normals_program};

        auto object = Object::build_new_object(points, 3, programs, fun, color);
        object->scale(5, 5, 5);

        scene->add_object(object);
    }

    return scene;
}
