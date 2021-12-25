#pragma once

#include "particles/generator.hh"
#include "particles/fireflies_particle.hh"

class FirefliesGenerator : public ParticleGenerator
{
public:
    FirefliesGenerator(misc::Vector3<float> pos, shared_program program);

    void generate(unsigned n) override;

    void update(double delta_time) override;

    static inline misc::Vector3<float> firefly_color{99.2 / 100, 1, 31.8 / 100};

private:
    std::list<FirefliesParticle> fireflies_;
};
