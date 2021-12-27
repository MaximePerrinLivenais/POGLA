#include "program.hh"

#include <fstream>
#include <vector>
#include <iostream>

Program::Program(std::string vertex_shader_src,
                 optional_string tess_control_shader_src,
                 optional_string tess_evaluation_shader_src,
                 optional_string geometry_shader_src,
                 std::string fragment_shader_src,
                 std::function<void()> drawing_function)
{
    ready_ = false;
    drawing_function_ = drawing_function;

    // Get a program object.
    GLuint program = glCreateProgram();

    auto vertex_shader = compile(vertex_shader_src, GL_VERTEX_SHADER);
    if (!vertex_shader)
        return;

    glAttachShader(program, *vertex_shader);

    std::optional<GLuint> tess_control_shader = std::nullopt;
    std::optional<GLuint> tess_evaluation_shader = std::nullopt;
    if (tess_control_shader_src && tess_evaluation_shader_src)
    {
        tess_control_shader =
            compile(*tess_control_shader_src, GL_TESS_CONTROL_SHADER);
        if (!tess_control_shader)
            return;

        tess_evaluation_shader =
            compile(*tess_evaluation_shader_src, GL_TESS_EVALUATION_SHADER);
        if (!tess_evaluation_shader)
            return;

        glAttachShader(program, *tess_control_shader);
        glAttachShader(program, *tess_evaluation_shader);
    }

    std::optional<GLuint> geometry_shader = std::nullopt;
    if (geometry_shader_src)
    {
        geometry_shader = compile(*geometry_shader_src, GL_GEOMETRY_SHADER);
        if (!geometry_shader)
            return;

        glAttachShader(program, *geometry_shader);
    }

    auto fragment_shader = compile(fragment_shader_src, GL_FRAGMENT_SHADER);
    if (!fragment_shader)
        return;

    glAttachShader(program, *fragment_shader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(*vertex_shader);
        if (tess_control_shader)
            glDeleteShader(*tess_control_shader);
        if (tess_evaluation_shader)
            glDeleteShader(*tess_evaluation_shader);
        if (geometry_shader)
            glDeleteShader(*geometry_shader);
        glDeleteShader(*fragment_shader);

        logs_ = std::string(infoLog.data());

        // In this simple program, we'll just leave
        return;
    }

    program_ = program;
    ready_ = true;

    glDetachShader(program, *vertex_shader);
    if (tess_control_shader)
        glDetachShader(program, *tess_control_shader);
    if (tess_evaluation_shader)
        glDetachShader(program, *tess_evaluation_shader);
    if (geometry_shader)
        glDetachShader(program, *geometry_shader);
    glDetachShader(program, *fragment_shader);

    glDeleteShader(*vertex_shader);
    if (tess_control_shader)
        glDeleteShader(*tess_control_shader);
    if (tess_evaluation_shader)
        glDeleteShader(*tess_evaluation_shader);
    if (geometry_shader)
        glDeleteShader(*geometry_shader);
    glDeleteShader(*fragment_shader);
}

Program::~Program()
{}

std::optional<GLuint> Program::compile(std::string shader_src,
                                       GLint shader_type)
{
    std::string source_str;
    auto shader_stream = std::ifstream(shader_src);
    if (!shader_stream.is_open())
    {
        logs_ = "Can not open file " + shader_src;
        return std::nullopt;
    }

    std::getline(shader_stream, source_str, '\0');

    GLuint shader = glCreateShader(shader_type);

    const GLchar* source = source_str.c_str();

    glShaderSource(shader, 1, &source, 0);

    glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(shader);

        logs_ = std::string(infoLog.data());

        // In this simple program, we'll just leave
        return std::nullopt;
    }

    return shader;
}

shared_program Program::make_program(std::string vertex_shader_src,
                                     std::string fragment_shader_src,
                                     std::function<void()> drawing_function)
{
    return std::make_shared<Program>(vertex_shader_src, std::nullopt,
                                     std::nullopt, std::nullopt,
                                     fragment_shader_src, drawing_function);
}

shared_program Program::make_program(std::string vertex_shader_src,
                                     std::string tess_control_shader_src,
                                     std::string tess_evaluation_shader_src,
                                     std::string fragment_shader_src,
                                     std::function<void()> drawing_function)
{
    return std::make_shared<Program>(vertex_shader_src, tess_control_shader_src,
                                     tess_evaluation_shader_src, std::nullopt,
                                     fragment_shader_src, drawing_function);
}

shared_program Program::make_program(std::string vertex_shader_src,
                                     std::string geometry_shader_src,
                                     std::string fragment_shader_src,
                                     std::function<void()> drawing_function)
{
    return std::make_shared<Program>(vertex_shader_src, std::nullopt,
                                     std::nullopt, geometry_shader_src,
                                     fragment_shader_src, drawing_function);
}

shared_program Program::make_program(std::string vertex_shader_src,
                                     std::string tess_control_shader_src,
                                     std::string tess_evaluation_shader_src,
                                     std::string geometry_shader_src,
                                     std::string fragment_shader_src,
                                     std::function<void()> drawing_function)
{
    return std::make_shared<Program>(
        vertex_shader_src, tess_control_shader_src, tess_evaluation_shader_src,
        geometry_shader_src, fragment_shader_src, drawing_function);
}

void Program::use()
{
    glUseProgram(program_);
}

GLuint Program::id_get()
{
    return program_;
}

std::string Program::get_log()
{
    return logs_;
}

bool Program::is_ready()
{
    return ready_;
}

void Program::draw() const
{
    drawing_function_();
}

GLuint Program::get_attrib_loc(std::string variable) const
{
    return glGetAttribLocation(program_, variable.c_str());
}

void Program::update_uniform(std::string variable, const misc::Matrix4& matrix)
{
    GLuint var_location = glGetUniformLocation(program_, variable.c_str());

    glUniformMatrix4fv(var_location, 1, false, matrix.transpose().data());
}

void Program::update_uniform(std::string variable,
                             const misc::Vector3<float>& vec3)
{
    GLuint var_location = glGetUniformLocation(program_, variable.c_str());

    float data[3] = {vec3.x, vec3.y, vec3.z};

    glUniform3fv(var_location, 1, data);
}

void Program::update_uniform(std::string variable, float f)
{
    GLuint var_location = glGetUniformLocation(program_, variable.c_str());
    glUniform1f(var_location, f);
}

void Program::update_uniform(std::string variable, const misc::Texture& texture)
{
    GLuint var_location = glGetUniformLocation(program_, variable.c_str());
    glUniform1i(var_location, texture.get_texture_unit_id());
}
