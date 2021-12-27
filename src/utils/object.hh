#pragma once

#include <functional>
#include <optional>

#include "misc/matrix4.hh"
#include "program.hh"
#include "scene/scene_data.hh"
#include "texture.hh"
#include "vao.hh"

class Object;

using optional_float = std::optional<float>;
using optional_float_vec3 = std::optional<misc::Vector3<float>>;
using shared_object = std::shared_ptr<Object>;

class Object
{
public:
    Object(const std::vector<shared_program> programs,
           const std::function<void()>& drawing_function,
           const optional_float_vec3 color, const optional_float diffuse,
           const optional_float specular);

    static shared_object
    build_new_object(const std::vector<float>& points,
                     const size_t element_size,
                     const std::vector<shared_program> programs,
                     const std::function<void()>& drawing_function,
                     const optional_float_vec3 color = std::nullopt,
                     const optional_float diffuse = std::nullopt,
                     const optional_float specular = std::nullopt);

    void translate(float x, float y, float z);
    void rotation(float x, float y, float z);
    void scale(float x, float y, float z);

    void add_vbo(const std::vector<float>& values, unsigned int id, GLint size);

    void set_texture(shared_texture texture);
    void set_programs(std::vector<shared_program> program);

    void set_location(misc::Vector3<float> pos);

    unsigned int nb_triangles() const;
    void bind();

    misc::Matrix4 get_model_matrix() const;
    optional_float_vec3 get_color() const;
    optional_float get_diffuse() const;
    optional_float get_specular() const;
    int get_texture_unit_id() const;

    void draw(const Scene_data& data);

private:
    misc::Vao vao_;
    misc::Matrix4 model_matrix_;

    optional_float_vec3 color_;
    optional_float diffuse_coef_;
    optional_float specular_coef_;

    shared_texture texture_;

    std::vector<shared_program> programs_;

    std::function<void()> drawing_function_;
};
