#include <Mapgen-Lib/Generators/Naive.hpp>
#include <Mapgen-Lib/IO.hpp>

int main()
{
	Generators::Generator* generator = new Generators::Naive();

	Matrix2f map (50, 100);

	generator->Generate(map);
	
	if (IO::SaveMap("maps/map.txt", map))
		std::cout << "The generated map has been successfully saved.\n";
	else
	{
		std::cerr << "[Mapgen-App] error: an error occured during the saving process of the map.\n";
		return 1;
	}

	generator->Smoothe(map);
	
	if (IO::SaveMap("maps/map_smooth.txt", map))
		std::cout << "The generated and smoothed map has been successfully saved.\n";
	else
	{
		std::cerr << "[Mapgen-App] error: an error occured during the saving process of the smoothed map.\n";
		return 1;
	}

	delete generator;

	return 0;
}
