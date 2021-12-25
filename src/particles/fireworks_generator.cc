#include "particles/fireworks_generator.hh"
#include <random>
#include <iostream>
#include <cmath>

FireworksGenerator::FireworksGenerator(misc::Vector3<float> pos,
                                       misc::Vector3<float> color, float speed,
                                       double gen_frequence,
                                       shared_program program)
    : ParticleGenerator(pos, {0, 0, 0}, color, speed, gen_frequence, 500,
                        program)

{}

misc::Vector3<float> FireworksGenerator::compute_gravity(double time)
{
    float y = -(1.0 / 2.0) * 9.8 * time * time;

    return {0, y, 0};
}

misc::Vector3<float>
FireworksGenerator::compute_trajectory(double time, misc::Vector3<float> origin,
                                       misc::Vector3<float> direction,
                                       float speed)
{
    float x = origin.x + direction.x * speed * time;
    float y = origin.y + direction.y * speed * time;
    float z = origin.z + direction.z * speed * time;

    return misc::Vector3<float>{x, y, z} + compute_gravity(time);
}

void FireworksGenerator::blow(const Particle& rocket)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0, 1.0);

    for (unsigned i = 0; i < gen_number_; i++)
    {
        misc::Vector3<float> random_vec{dis(gen), dis(gen), dis(gen)};
        random_vec = random_vec.normalize();
        auto particle_pos = rocket.position;

        particles_.emplace_back(Particle{particle_pos, random_vec, rocket.color,
                                         rocket.speed, 2, 1});
    }
}

void FireworksGenerator::generate(unsigned)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0, 1.0);

    misc::Vector3<float> random_vec{dis(gen), dis(gen) + 3, dis(gen)};
    random_vec = random_vec.normalize();

    rockets_.emplace_back(Particle{position_, random_vec, color_, 35, 2, 5});
}

void FireworksGenerator::generate_rocket_trails(
    const misc::Vector3<float>& pos, const misc::Vector3<float>& dir,
    const misc::Vector3<float>& color, float size, float life,
    unsigned nb_trail)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0, 1.0);

    for (unsigned i = 0; i < nb_trail; i++)
    {
        misc::Vector3<float> random_vec{dis(gen), dis(gen), dis(gen)};
        random_vec = (dir * 4 + random_vec).normalize();

        rocket_trails_.emplace_back(
            Particle(random_vec + pos, {0, 0, 0}, color * 0.6, 1, size, life));
    }
}

void FireworksGenerator::update_rockets(double delta_time)
{
    for (auto it = rockets_.begin(); it != rockets_.end();)
    {
        double t = it->total_life - it->remaining_life;

        auto position =
            compute_trajectory(t, it->position, it->direction, it->speed);

        auto dir =
            (compute_gravity(t) * -1 - it->direction * it->speed).normalize();

        generate_rocket_trails(position, dir, it->color, 5, 0.25, 20);

        it->remaining_life -= delta_time;
        if (it->remaining_life < 0)
        {
            it->position = position;
            blow(*it);
            it = rockets_.erase(it);
        }

        else
            it++;
    }
}

void FireworksGenerator::update_particles(double delta_time)
{
    for (auto it = particles_.begin(); it != particles_.end();)
    {
        float t = it->total_life - it->remaining_life;

        auto position =
            compute_trajectory(t, it->position, it->direction, it->speed);
        auto alpha = it->remaining_life / it->total_life;

        trails_.emplace_back(Particle(position, it->direction, it->color,
                                      it->speed, 4, 0.3, alpha));

        it->remaining_life -= delta_time;
        if (it->remaining_life < 0)
            it = particles_.erase(it);

        else
        {
            add_particle(position, it->color, alpha, it->size);
            it++;
        }
    }
}

void FireworksGenerator::update_trails(double delta_time)
{
    for (auto it = trails_.begin(); it != trails_.end();)
    {
        it->remaining_life -= delta_time;
        if (it->remaining_life < 0)
            it = particles_.erase(it);

        else
        {
            auto alpha = it->remaining_life / it->total_life;
            add_particle(it->position, it->color, it->alpha * alpha, it->size);
            it++;
        }
    }
}
void FireworksGenerator::update_rocket_trails(double delta_time)
{
    for (auto it = rocket_trails_.begin(); it != rocket_trails_.end();)
    {
        it->remaining_life -= delta_time;
        it->position += it->direction * it->speed * delta_time;

        if (it->remaining_life < 0)
            it = particles_.erase(it);

        else
        {
            float life = it->remaining_life / it->total_life;
            float size = it->size;

            add_particle(it->position, it->color, it->alpha * life, size);
            it++;
        }
    }
}

void FireworksGenerator::update(double delta_time)
{
    update_gen_timer(delta_time);
    particles_positions_.clear();
    particles_colors_.clear();
    particles_size_.clear();

    update_rockets(delta_time);
    update_particles(delta_time);
    update_trails(delta_time);
    update_rocket_trails(delta_time);
}
