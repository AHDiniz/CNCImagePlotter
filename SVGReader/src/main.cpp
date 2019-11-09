#include <iostream>
#include <cstring>
#include <cstdlib>

#include "config.hpp"
#include "parser.hpp"

/**
 * SVG File parser:
 * 
 * Basic usage: plotter -f <<SVG file name>> -p <<arduino serial port (optional)>> -d <<Width of plot>> <<Height of plot>>
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
 * 	-> Lines (end points)
 * 	-> Rectangles (center, width and height)
 * 	-> Circles (center and radius)
 * 	-> Ellipses (center, width and height)
 * 	-> Polyline (point sequence)
 * 	-> Polygon (point sequence)
 * 	-> Path (currently not supported)
 * 	-> Text (currently not supported)
 * 
 * 1 - Read SVG file
 * 2 - Simplify data
 * 3 - Print GCode file
 * 4 - Send GCode file to Arduino
*/

static void PrintHelp(void)
{
	std::cout << "Arduino CNC SVG Plotter" << std::endl << std::endl;

	std::cout << "Usage:" << std::endl;
	std::cout << "-f to tell the file location" << std::endl;
	std::cout << "-p to specify the serial port where the arduino is connected (default is 'Put default here')" << std::endl;
	std::cout << "-d to specify the dimensions of the plot in milimeters (default is 80 60)" << std::endl;
	std::cout << "-h to display this help message" << std::endl << std::endl;

	std::cout << "Supported geometries:" << std::endl;
	std::cout << "Lines: end points" << std::endl;
	std::cout << "Rectangles: center, width and height" << std::endl;
	std::cout << "Circles: center and radius" << std::endl;
	std::cout << "Ellipses: center, width and height" << std::endl;
	std::cout << "Polyline: point sequence" << std::endl;
	std::cout << "Polygon: point sequence" << std::endl;
}

int main(int argc, char *argv[])
{
	Config *config = Config::GetInstance();

	for (int i = 1; i < argc;)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			PrintHelp();
			return EXIT_SUCCESS;
		}
		else if (strcmp(argv[i], "-p") == 0)
		{
			if (i + 1 >= argc)
			{
				std::cout << "Unspecified input. Type 'plotter -h' to get help." << std::endl;
				return EXIT_SUCCESS;
			}

			config->SetPort(argv[i + 1]);
			i += 2;
		}
		else if (strcmp(argv[i], "-f") == 0)
		{
			if (i + 1 >= argc)
			{
				std::cout << "Unspecified input. Type 'plotter -h' to get help." << std::endl;
				return EXIT_SUCCESS;
			}

			config->SetFilename(argv[i + 1]);
			i += 2;
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			if (i + 2 >= argc)
			{
				std::cout << "Unspecified input. Type 'plotter -h' to get help." << std::endl;
				return EXIT_SUCCESS;
			}

			int w = atoi(argv[i + 1]);
			int h = atoi(argv[i + 2]);

			config->SetHeight(h);
			config->SetWidth(w);

			i += 3;
		}
		else
		{
			std::cout << "Unspecified input. Type 'plotter -h' to get help." << std::endl;
			return EXIT_SUCCESS;
		}
	}

	if (config->GetFilename().empty())
	{
		std::cout << "Input file not specified. Type 'plotter -h' to get help." << std::endl;
		return EXIT_SUCCESS;
	}

	if (config->GetPort().empty())
		config->SetPort("TODO: Default serial port.");

	if (config->GetWidth() <= 0) config->SetWidth(80);
	if (config->GetHeight() <= 0) config->SetHeight(60);

	std::vector<Forms::Form*> forms = Parser::ReadSVGFile();
	std::vector<Forms::Point> points;

	for (auto form : forms)
	{
		auto drawPoints = form->Draw();
		for (auto p : drawPoints) points.push_back(p);
	}

	for (auto p : points) std::cout << p.x << " " << p.y << std::endl;

	return EXIT_SUCCESS;
}
