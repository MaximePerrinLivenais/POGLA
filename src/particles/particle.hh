#pragma once

#include "misc/vector3.hh"

struct Particle
{
    Particle(misc::Vector3<float> position, misc::Vector3<float> direction,
             misc::Vector3<float> color, float speed, float size, float life,
             float alpha = 1)
        : position(position)
        , direction(direction)
        , color(color)
        , speed(speed)
        , size(size)
        , total_life(life)
        , remaining_life(life)
        , alpha(alpha)
    {}

    misc::Vector3<float> position;
    misc::Vector3<float> direction;
    misc::Vector3<float> color;
    float speed;
    float size;
    float total_life;
    float remaining_life;
    float alpha;
};
