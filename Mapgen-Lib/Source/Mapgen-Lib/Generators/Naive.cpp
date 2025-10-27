#include <Mapgen-Lib/Generators/Naive.hpp>

namespace Generators
{
    Naive::Naive()
    {
        std::random_device rng;
        m_Rng = std::mt19937(rng());
    }

    float Naive::Uniform(float a, float b)
    {
        std::uniform_real_distribution<> d(a, b);
        return d(m_Rng);
    }

    void Naive::Generate(Matrix2f& map)
    {
        const uint delta = 160;

        uint height = map.GetShape().y, width = map.GetShape().x;

        float val;

        for (uint y = 0; y < height; y++)
        {
            for (uint x = 0; x < width; x++)
            {
                if (x > 0 && y > 0)
                {
                    val = Uniform(map(x, y-1) - delta, map(x, y-1) + delta);
                    val += Uniform(map(x-1, y) - delta, map(x-1, y) + delta);
                    val /= 2;
                }
                else if (y > 0)
                {
                    val = Uniform(map(x, y-1) - delta, map(x, y-1) + delta);
                }
                else if (x > 0)
                {
                    val = Uniform(map(x-1, y) - delta, map(x-1, y) + delta);
                }
                else
                {
                    val = Uniform(0, width);
                }
                map(x, y) = val;
            }
        }
    }

    void Naive::Smoothe(Matrix2f& map)
    {
        Matrix2f map_smth (map.GetShape());

        float s;

        // center
        for (uint x = 1; x < map.GetShape().x - 1; x++)
        {
            for (uint y = 1; y < map.GetShape().y - 1; y++)
            {
                s = map(x - 1, y - 1);
                s += map(x - 1, y);
                s += map(x - 1, y + 1);
                s += map(x, y - 1);
                s += map(x, y);
                s += map(x, y + 1);
                s += map(x + 1, y - 1);
                s += map(x + 1, y);
                s += map(x + 1, y + 1);
                map_smth(x, y) = s / 9;
            }
        }

        uint nb_points;
        // weastern and eastern sides
        for (uint y = 0; y < map.GetShape().y; y++)
        {
            // weastern
            s = 0;
            nb_points = 0;
            if (y > 0)
            {
                s += map(0, y - 1);
                s += map(1, y - 1);
                nb_points += 2;
            }

            if (y < map.GetShape().y - 1)
            {
                s += map(0, y + 1);
                s += map(1, y + 1);
                nb_points += 2;
            }

            s += map(0, y);
            s += map(1, y);
            nb_points += 2;

            map_smth(0, y) = s / nb_points;

            // eastern
            s = 0;
            nb_points = 0;
            if (y > 0)
            {
                s += map(map.GetShape().x - 1, y - 1);
                s += map(map.GetShape().x - 2, y - 1);
                nb_points += 2;
            }

            if (y < map.GetShape().y - 1)
            {
                s += map(map.GetShape().x - 1, y + 1);
                s += map(map.GetShape().x - 2, y + 1);
                nb_points += 2;
            }

            s += map(map.GetShape().x - 1, y);
            s += map(map.GetShape().x - 2, y);
            nb_points += 2;

            map_smth(map.GetShape().x - 1, y) = s / nb_points;
        }

        // northern and southern sides
        for (uint x = 1; x < map.GetShape().x - 1; x++)
        {
            // northern
            s = 0;
            s += map(x - 1, 0);
            s += map(x - 1, 1);
            s += map(x, 0);
            s += map(x, 1);
            s += map(x + 1, 0);
            s += map(x + 1, 1);
            map_smth(x, 0) = s / 6;

            // southern
            s = 0;
            s += map(x - 1, map.GetShape().y - 1);
            s += map(x - 1, map.GetShape().y - 2);
            s += map(x, map.GetShape().y - 1);
            s += map(x, map.GetShape().y - 2);
            s += map(x + 1, map.GetShape().y - 1);
            s += map(x + 1, map.GetShape().y - 2);
            map_smth(x, map.GetShape().y - 1) = s / 6;
        }

        map = std::move(map_smth);
    }
}
