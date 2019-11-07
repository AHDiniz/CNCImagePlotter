#include "svgparser.hpp"
#include "config.hpp"

#include <iostream>
#include <cstdlib>
#include <cstring>

namespace SVG
{
	const std::vector<Forms::Form> &ReadSVGFile()
	{
		std::vector<Forms::Form> result;

		Config *config = Config::GetInstance();

		TiXmlDocument doc;
		doc.LoadFile(config->GetFilename());

		TiXmlElement *node = doc.FirstChildElement();

		int width, height;
		node->QueryIntAttribute("width", &width);
		node->QueryIntAttribute("height", &height);

		if (width != config->GetWidth() || height != config->GetHeight())
		{
			std::cout << "OOPS! The dimensions of the SVG image are different then the ones given by the program. Please change them!" << std::endl;
			exit(EXIT_FAILURE);
		}

		for (TiXmlElement *e = node->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		{
			const char *name = e->Value();

			if (strcmp(name, "line") == 0)
			{

			}
			else if (strcmp(name, "rect") == 0)
			{

			}
			else if (strcmp(name, "circle") == 0)
			{

			}
			else if (strcmp(name, "ellipse") == 0)
			{

			}
			else if (strcmp(name, "polyline") == 0)
			{

			}
			else if (strcmp(name, "polygon") == 0)
			{

			}
			else if (strcmp(name, "text") == 0)
			{
				
			}
		}

		return result;
	}
}
