#include "parser.hpp"
#include "config.hpp"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

namespace Parser
{
	const std::vector<Forms::Form*> ReadSVGFile()
	{
		std::vector<Forms::Form*> result;

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
				float x1, y1, x2, y2;

				e->QueryFloatAttribute("x1", &x1);
				e->QueryFloatAttribute("y1", &y1);
				e->QueryFloatAttribute("x2", &x2);
				e->QueryFloatAttribute("y2", &y2);

				Forms::Line *l = new Forms::Line();
				l->a = {x1, y1};
				l->b = {x2, y2};

				result.push_back(l);
			}
			else if (strcmp(name, "rect") == 0)
			{
				float x, y, width, height;

				e->QueryFloatAttribute("x", &x);
				e->QueryFloatAttribute("y", &y);
				e->QueryFloatAttribute("width", &width);
				e->QueryFloatAttribute("height", &height);

				Forms::Rect *r = new Forms::Rect();
				r->center = {x, y};
				r->width = width;
				r->height = height;

				result.push_back(r);
			}
			else if (strcmp(name, "circle") == 0)
			{
				float cx, cy, r;

				e->QueryFloatAttribute("cx", &cx);
				e->QueryFloatAttribute("cy", &cy);
				e->QueryFloatAttribute("r", &r);

				Forms::Circle *c = new Forms::Circle();
				c->center = {cx, cy};
				c->radius = r;

				result.push_back(c);
			}
			else if (strcmp(name, "ellipse") == 0)
			{
				float rx, ry, cx, cy;

				e->QueryFloatAttribute("rx", &rx);
				e->QueryFloatAttribute("ry", &ry);
				e->QueryFloatAttribute("cx", &cx);
				e->QueryFloatAttribute("cy", &cy);

				Forms::Ellipse *e = new Forms::Ellipse();
				e->center = {cx, cy};
				e->width = rx;
				e->height = ry;

				result.push_back(e);
			}
			else if (strcmp(name, "polyline") == 0)
			{
				std::vector<Forms::Point> points;

				std::string data;

				e->QueryStringAttribute("points", &data);

				std::stringstream stream(data);

				float x, y;
				while (stream >> x >> y)
				{
					Forms::Point p = {x, y};
					points.push_back(p);
				}

				Forms::Polyline *p = new Forms::Polyline();
				p->vertices = points;

				result.push_back(p);
			}
			else if (strcmp(name, "polygon") == 0)
			{
				std::vector<Forms::Point> points;

				std::string data;

				e->QueryStringAttribute("points", &data);

				std::stringstream stream(data);

				float x, y;
				while (stream >> x >> y)
				{
					Forms::Point p = {x, y};
					points.push_back(p);
				}

				Forms::Polygon *p = new Forms::Polygon();
				p->vertices = points;

				result.push_back(p);
			}
			// else if (strcmp(name, "text") == 0)
			// {
			// 	const char *text = e->GetText();

			// 	float fontSize;

			// 	e->QueryFloatAttribute("font-size", &fontSize);

			// 	Forms::Text *t = new Forms::Text();
			// 	t->fontSize = fontSize;
			// 	t->text = text;

			// 	result.push_back(t);
			// }
		}

		return result;
	}

	const char *GCodeCreator(const std::vector<Forms::Form*> forms)
	{
		/**
		 * GCode:
		 * Set G21 to use milimeters
		 * Use F to set feed rate
		 * Speed data: G00 = max speed, G01 = feed rate speed
		*/

		std::stringstream stream;

		Config *config = Config::GetInstance();

		/* Initialization */ {

			// Starting the program:
			stream << "%" << std::endl; // GCode start
			stream << "O100" << std::endl; // Program ID

			// Program setup data:
			stream << "G21 F" << config->GetFeedrate() << std::endl;
			stream << "G00 Z5" << std::endl;
			stream << "G00 X0 Y0" << std::endl;
		}

		/* Drawing each form */ {

			// Getting plotter coordinate system:
			float width = config->GetWidth() / 2;
			float height = config->GetHeight() / 2;

			for (auto f : forms)
			{
				std::vector<Forms::Point> points = f->Draw();

				// Going to the first point:
				stream << "G00 " << std::endl;
				stream << "X" << points[0].x - width << " Y" << points[0].y - height << std::endl;

				stream << "Z0" << std::endl;
				stream << "G01" << std::endl;
				// Drawing the other points:
				for (int i = 1; i < points.size(); ++i)
				{
					stream << "X" << points[i].x - width << " Y" << points[i].y - height << std::endl;
				}
				stream << "G00 Z5" << std::endl;
			}
		}

		/* Finalization */ {

			stream << "G00 X0Y0" << std::endl;
			stream << "%" << std::endl;
		}

		std::string gCode = stream.str();
		const char *result = strdup(gCode.c_str());

		return result;
	}
}
