#pragma once

#include "particles/particle.hh"
#include "misc/vao.hh"
#include "program.hh"
#include "misc/matrix4.hh"
#include <list>

class ParticleGenerator
{
public:
    ParticleGenerator(misc::Vector3<float> pos, misc::Vector3<float> dir,
                      misc::Vector3<float> color, float speed,
                      double gen_frequence, unsigned gen_number,
                      shared_program program);

    void set_program(shared_program program);
    virtual void generate(unsigned n);

    void bind();
    virtual void update(double delta_time);
    virtual void draw(const misc::Matrix4& v_matrix,
                      const misc::Matrix4& p_matrix);

protected:
    void update_gen_timer(double delta_time);
    void add_particle(misc::Vector3<float> pos, misc::Vector3<float> color,
                      float alpha, float size);

protected:
    misc::Vector3<float> position_;
    misc::Vector3<float> direction_;
    misc::Vector3<float> color_;
    float speed_;

    double time_next_gen_;
    double gen_frequence_;
    unsigned gen_number_;

    shared_program program_;

    std::list<Particle> particles_;

    std::vector<float> particles_positions_;
    std::vector<float> particles_colors_;
    std::vector<float> particles_size_;

    misc::Vao vao_;
    std::shared_ptr<misc::Vbo> particles_pos_vbo_;
    std::shared_ptr<misc::Vbo> color_vbo_;
    std::shared_ptr<misc::Vbo> size_vbo_;
};
