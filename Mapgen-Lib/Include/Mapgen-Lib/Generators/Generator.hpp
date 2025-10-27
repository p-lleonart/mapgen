#pragma once

#include <Mapgen-Lib/Matrix2.hpp>

using uint = unsigned int;

namespace Generators
{
    struct Generator
    {
        Generator()
        {
        }
        virtual ~Generator() = default;

        /**
         * It is the entry point of the algorithm.
         * 
         * This virtual method must be implemented inside of children.
         */
        virtual void Generate(Matrix2f&) = 0;

        /**
         * This method might not be needed by every algorithm in the future so it can't be mandatory.
         */
        virtual void Smoothe(Matrix2f&)
        {
        }
    };
}
