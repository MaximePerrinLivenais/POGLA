#include "particles/snow_generator.hh"
#include <random>

SnowGenerator::SnowGenerator(shared_program program)
    : ParticleGenerator({0, 100, 0}, {0, -1, 0}, {1, 1, 1}, 2, 0.05, 50,
                        program)
{}

void SnowGenerator::generate(unsigned n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-100.0, 100.0);

    for (unsigned i = 0; i < n; i++)
    {
        misc::Vector3<float> random_vec{dis(gen), dis(gen), dis(gen)};

        particles_.emplace_back(Particle{position_ + random_vec, direction_,
                                         color_, speed_, 2, 15});
    }
}
