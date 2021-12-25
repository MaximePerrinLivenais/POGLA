#pragma once
#include "particles/generator.hh"

class FireworksGenerator : public ParticleGenerator
{
public:
    FireworksGenerator(misc::Vector3<float> pos, misc::Vector3<float> color,
                       float speed, double gen_frequence,
                       shared_program program);

    void generate(unsigned n) override;

    void update(double delta_time) override;

    misc::Vector3<float> compute_trajectory(double time,
                                            misc::Vector3<float> origin,
                                            misc::Vector3<float> direction,
                                            float speed);

    misc::Vector3<float> compute_gravity(double time);
    void blow(const Particle& rocket);

private:
    void update_rockets(double delta_time);
    void update_particles(double delta_time);
    void update_trails(double delta_time);
    void update_rocket_trails(double delta_time);

    void generate_rocket_trails(const misc::Vector3<float>& pos,
                                const misc::Vector3<float>& dir,
                                const misc::Vector3<float>& color, float size,
                                float life, unsigned nb_trail);

private:
    std::list<Particle> rockets_;
    std::list<Particle> trails_;
    std::list<Particle> rocket_trails_;
};
