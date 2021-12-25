#pragma once

#include "particles/particle.hh"

struct FirefliesParticle : public Particle
{
    FirefliesParticle(misc::Vector3<float> position,
                      misc::Vector3<float> direction,
                      misc::Vector3<float> color, float speed, float size,
                      float life, float alpha = 1)
        : Particle(position, direction, color, speed, size, life, alpha)
        , prev_direction({0, 0, 0})
    {}

    misc::Vector3<float> prev_direction;
};
