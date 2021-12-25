#include "object.hh"

Object::Object(const shared_program program,
                const std::function<void()>& drawing_function,
                const optional_float_vec3 color,
                const optional_float diffuse,
                const optional_float specular)
    : vao_()
    , model_matrix_(misc::Matrix4::identity())
    , color_(color)
    , diffuse_coef_(diffuse)
    , specular_coef_(specular)
    , texture_(nullptr)
    , program_(program)
    , drawing_function_(drawing_function)

{}

shared_object Object::build_new_object(const std::vector<float>& points,
                                            const size_t element_size,
                                            const shared_program program,
                                            const std::function<void()>& drawing_function,
                                            const optional_float_vec3 color,
                                            const optional_float diffuse,
                                            const optional_float specular)
{
    auto object = std::make_shared<Object>(program,
                                            drawing_function,
                                            color,
                                            diffuse,
                                            specular);

    object->add_vbo(points, 0, element_size);

    return object;
}



void Object::translate(float x, float y, float z)
{
    model_matrix_.translate(x, y, z);
}

void Object::rotation(float x, float y, float z)
{
    model_matrix_.rotation(x, y, z);
}

void Object::scale(float x, float y, float z)
{
    model_matrix_.scale(x, y, z);
}

void Object::add_vbo(const std::vector<float>& values, unsigned int id,
                     GLint size)
{
    vao_.bind();
    vao_.add_vbo(std::make_shared<misc::Vbo>(values, id, size));
}

void Object::set_texture(shared_texture texture)
{
    texture_ = texture;
}

void Object::set_program(shared_program program)
{
    program_ = program;
}

void Object::set_location(misc::Vector3<float> pos)
{
    model_matrix_.set(0, 3, pos.x);
    model_matrix_.set(1, 3, pos.y);
    model_matrix_.set(2, 3, pos.z);
}

unsigned int Object::nb_triangles() const
{
    return vao_.nb_triangles();
}

optional_float_vec3 Object::get_color() const
{
    return color_;
}

optional_float Object::get_diffuse() const
{
    return diffuse_coef_;
}

optional_float Object::get_specular() const
{
    return specular_coef_;
}

int Object::get_texture_unit_id() const
{
    return texture_->get_texture_unit_id();
}

void Object::bind()
{
    program_->use();
    vao_.bind();
}

misc::Matrix4 Object::get_model_matrix() const
{
    return model_matrix_;
}

#include <iostream>

void Object::draw(const Scene_data& data)
{
    bind();

    auto mvp = data.vp_matrix;
    mvp *= get_model_matrix();

    program_->update_uniform("camera_position", data.camera_position);

    if (color_)
        program_->update_uniform("object_color", *color_);
    if (diffuse_coef_)
        program_->update_uniform("diffuse", *diffuse_coef_);
    if (specular_coef_)
        program_->update_uniform("specular", *specular_coef_);
    if (texture_)
        program_->update_uniform("texture_sampler1", *texture_);

    program_->update_uniform("mvp_matrix", mvp);

    drawing_function_();
}
