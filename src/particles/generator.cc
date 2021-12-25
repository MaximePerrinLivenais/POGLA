#include "particles/generator.hh"
#include "misc/matrix4.hh"
#include <iostream>

ParticleGenerator::ParticleGenerator(misc::Vector3<float> pos,
                                     misc::Vector3<float> dir,
                                     misc::Vector3<float> color, float speed,
                                     double gen_frequence, unsigned gen_number,
                                     shared_program program)

    : position_(pos)
    , direction_(dir)
    , color_(color)
    , speed_(speed)
    , time_next_gen_(gen_frequence)
    , gen_frequence_(gen_frequence)
    , gen_number_(gen_number)
    , program_(program)
{
    auto position_loc = program->get_attrib_loc("position");
    auto color_loc = program->get_attrib_loc("color");
    auto size_loc = program->get_attrib_loc("size");

    particles_pos_vbo_ =
        std::make_shared<misc::Vbo>(std::vector<float>(), position_loc, 3);

    color_vbo_ =
        std::make_shared<misc::Vbo>(std::vector<float>(), color_loc, 4);

    size_vbo_ = std::make_shared<misc::Vbo>(std::vector<float>(), size_loc, 1);

    vao_.add_vbo(particles_pos_vbo_);
    vao_.add_vbo(color_vbo_);
    vao_.add_vbo(size_vbo_);
}

void ParticleGenerator::set_program(shared_program program)
{
    program_ = program;
}

void ParticleGenerator::bind()
{
    program_->use();
    vao_.bind();
}

void ParticleGenerator::generate(unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        particles_.emplace_back(
            Particle{position_, direction_, color_, speed_, 0.5, 5});
    }
}

void ParticleGenerator::update_gen_timer(double delta_time)
{
    time_next_gen_ -= delta_time;
    if (time_next_gen_ < 0)
    {
        generate(gen_number_);
        time_next_gen_ = gen_frequence_;
    }
}

void ParticleGenerator::update(double delta_time)
{
    update_gen_timer(delta_time);

    particles_positions_.clear();
    particles_colors_.clear();
    for (auto it = particles_.begin(); it != particles_.end();)
    {
        it->position += it->direction * (delta_time * it->speed);
        if (it->position.y < 0 || it->remaining_life < 0)
            it = particles_.erase(it);

        else
        {
            add_particle(it->position, it->color,
                         it->remaining_life / it->total_life, it->size);
            it++;
        }
    }
}

void ParticleGenerator::add_particle(misc::Vector3<float> pos,
                                     misc::Vector3<float> color, float alpha,
                                     float size)
{
    particles_positions_.push_back(pos.x);
    particles_positions_.push_back(pos.y);
    particles_positions_.push_back(pos.z);

    particles_colors_.push_back(color.x);
    particles_colors_.push_back(color.y);
    particles_colors_.push_back(color.z);
    particles_colors_.push_back(alpha);

    particles_size_.push_back(size);
}

void ParticleGenerator::draw(const misc::Matrix4& v_matrix,
                             const misc::Matrix4& p_matrix)
{
    bind();

    program_->update_uniform("view_matrix", v_matrix);
    program_->update_uniform("proj_matrix", p_matrix);

    // update buffers
    particles_pos_vbo_->update(particles_positions_, 3);
    color_vbo_->update(particles_colors_, 4);
    size_vbo_->update(particles_size_, 1);

    glDrawArrays(GL_POINTS, 0, particles_pos_vbo_->get_nb_element());

    vao_.unbind_all();
}
