#include "fireflies_generator.hh"

#include <iostream>
#include <random>

FirefliesGenerator::FirefliesGenerator(misc::Vector3<float> pos,
                                       shared_program program)
    : ParticleGenerator(pos, {0, 0, 0}, firefly_color, 0, 0, 1, program)
{}

void FirefliesGenerator::generate(unsigned n)
{
    float distribution_range = 0.025;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-distribution_range,
                                              distribution_range);

    std::uniform_real_distribution<float> dis_pos(-15, 15);

    std::uniform_real_distribution<float> dis_life(1.4, 2.6);

    for (unsigned i = 0; i < n; i++)
    {
        fireflies_.emplace_back(FirefliesParticle{
            position_
                + misc::Vector3<float>{dis_pos(gen), dis_pos(gen),
                                       dis_pos(gen)},
            misc::Vector3<float>(dis(gen), dis(gen), dis(gen)), color_, speed_,
            5, dis_life(gen)});
    }
}

void FirefliesGenerator::update(double delta_time)
{
    particles_positions_.clear();
    particles_colors_.clear();
    particles_size_.clear();

    float distribution_range = 0.025;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-distribution_range,
                                              distribution_range);

    for (auto it = fireflies_.begin(); it != fireflies_.end(); it++)
    {
        it->remaining_life -= delta_time;

        if (it->remaining_life < 0)
        {
            it->prev_direction = it->direction;
            it->direction = misc::Vector3<float>(dis(gen), dis(gen), dis(gen));
            it->remaining_life = it->total_life;
        }

        auto direction_ratio = it->remaining_life / it->total_life;

        it->position += it->direction * (1 - direction_ratio)
            + it->prev_direction * direction_ratio;

        add_particle(it->position, it->color, 1, 1);
    }
}
