# mapgen

A fantasy map generator.

## Get started (development)

The project uses [davidtazy/cmake_virtual_mono_repo](https:://github.com/davidtazy/cmake_virtual_mono_repo)'s monorepo architecture. You'll need CMake and a C++ compiler.

Git fork the project, etc...

Then run ``cmake -B build`` (or ``cmake -B build -G "MinGW Makefiles`` if it doesn't work on Windows).

You may have an error, and to fix it, you have to search for all the ``all_Mapgen-XXX_enable`` inside ``build/CMakeCache.txt`` and set them to ``ON``.

Then re-type the cmake command, then cmake --build build, and finally run the executable file.
