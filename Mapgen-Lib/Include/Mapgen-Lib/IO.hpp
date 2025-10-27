#pragma once

#include <Mapgen-Lib/Matrix2.hpp>

namespace IO
{
    /**
     * Save a map inside of a file.
     * 
     * @returns ``true`` if the map has been successfully saved, ``false`` otherwise.
     */
    bool SaveMap(const char*, const Matrix2f&);
}
