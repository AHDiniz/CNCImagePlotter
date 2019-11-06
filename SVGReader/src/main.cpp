#include <iostream>
#include <cstring>
#include <cstdlib>

#include "config.hpp"

/**
 * SVG File parser:
 * 
 * Basic usage: plotter -f <<SVG file name>> -p <<arduino serial port (optional)>>
 * 
 * Will need to check if the image can be plotted by the arduino:
 * 	-> File check (existance and correct encoding)
 * 	-> Size check (see if the image is not too big for the arduino machine to plot)
 * 	-> Can't have images
 * 	-> Colors are ignored (only positions are considered)
 * 
 * Floating-point treatment: round or truncate?
 * 
 * Supported forms:
 * 	-> Lines (end points and thickness)
 * 	-> Rectangles (center, width, height and thickness)
 * 	-> Circles (center, radius and thickness)
 * 	-> Ellipses
 * 	-> Polyline
 * 	-> Polygon
 * 	-> Path
 * 	-> Text
*/

static void PrintHelp(void)
{
	std::cout << "Arduino CNC SVG Plotter" << std::endl << std::endl;

	std::cout << "Usage:" << std::endl;
	std::cout << "-f to tell the file location" << std::endl;
	std::cout << "-p to specify the serial port where the arduino is connected" << std::endl;
	std::cout << "-h to display this help message" << std::endl << std::endl;

	std::cout << "Supported geometries:" << std::endl;
	std::cout << "Lines: end points and thickness" << std::endl;
	std::cout << "Rectangles: center, width, height and border thickness" << std::endl;
	std::cout << "Circles: center, radius and border thickness" << std::endl;
}

int main(int argc, char *argv[])
{
	Config *config = Config::GetInstance();

	if (argc == 1)
	{
		PrintHelp();
		return EXIT_SUCCESS;
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1], "-h") == 0) PrintHelp();
		else std::cout << "Unspecified inputs. Type \"plotter -h\" to get help." << std::endl;
		return EXIT_SUCCESS;
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[2], "-h") == 0) PrintHelp();
		else if (strcmp(argv[1], "-f")) config->SetFilename(argv[2]);
		else if (strcmp(argv[1], "-p")) config->SetPort(argv[2]);
		else std::cout << "Unspecified inputs. Type \"plotter -h\" to get help." << std::endl;
		return EXIT_SUCCESS;
	}
}
