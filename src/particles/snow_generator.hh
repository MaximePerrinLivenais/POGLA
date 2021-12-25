#pragma once

#include "particles/generator.hh"

class SnowGenerator : public ParticleGenerator
{
public:
    SnowGenerator(shared_program program);

    void generate(unsigned n) override;
};
