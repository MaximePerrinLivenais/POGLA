#pragma once

#include <memory>
#include <optional>
#include <string>
#include <GL/glew.h>
#include "texture.hh"
#include "misc/matrix4.hh"
#include "misc/vector3.hh"

class Program;

using shared_program = std::shared_ptr<Program>;

using optional_string = std::optional<std::string>;

class Program
{
public:
    Program(std::string vertex_shader_src,
                optional_string tess_control_shader_src,
                optional_string tess_evaluation_shader_src,
                optional_string geometry_shader_src,
                std::string fragment_shader_src);
    ~Program();

    static shared_program make_program(std::string vertex_shader_src,
                                        std::string fragment_shader_src);

    static shared_program make_program(std::string vertex_shader_src,
                                        std::string tess_control_shader_src,
                                        std::string tess_evaluation_shader_src,
                                        std::string fragment_shader_src);

    static shared_program make_program(std::string vertex_shader_src,
                                        std::string geometry_shader_src,
                                        std::string fragment_shader_src);

    static shared_program make_program(std::string vertex_shader_src,
                                        std::string tess_control_shader_src,
                                        std::string tess_evaluation_shader_src,
                                        std::string geometry_shader_src,
                                        std::string fragment_shader_src);

    std::string get_log();
    bool is_ready();
    void use();
    GLuint id_get();

    std::optional<GLuint> compile(std::string shader_src, GLint shader_type);

    void update_uniform(std::string variable, const misc::Matrix4& matrix);
    void update_uniform(std::string variable, const misc::Vector3<float>& vec3);
    void update_uniform(std::string variable, float f);
    void update_uniform(std::string variable, const misc::Texture& texture);

    GLuint get_attrib_loc(std::string variable) const;

private:
    GLuint program_;
    bool ready_;
    std::string logs_;
};
