#pragma once

#include <Mapgen-Lib/Generators/Generator.hpp>

#include <random>

namespace Generators
{
    struct Naive : public Generator
    {
        Naive();
        void Generate(Matrix2f&) override;
        void Smoothe(Matrix2f&) override;
    private:
        std::mt19937 m_Rng;

        /**
         * Generates a number randomly inside of the specified interval.
         */
        float Uniform(float, float);
    };
}
