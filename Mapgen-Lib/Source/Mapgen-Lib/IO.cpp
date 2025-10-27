#include <Mapgen-Lib/IO.hpp>

#include <fstream>

bool IO::SaveMap(const char* filepath, const Matrix2f& map)
{
    std::ofstream F;
    F.open(filepath);

    if (F.is_open())
    {
        F << map.GetShape().x << " " << map.GetShape().y << "\n";
        F << map;
        return true;
    }
    else
    {
        std::cerr << "[Mapgen-Lib] error: the file '" << filepath << "' doesn't exist." << std::endl;
        return false;
    }
}
