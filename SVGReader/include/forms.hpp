#pragma once

#include <vector>

/**
 * Geometric forms data definitions
 * 
 * ? Maybe treat positions varying from -1 to 1
*/

namespace Forms
{
	struct Point
	{
		float x, y;
	};

	struct Line
	{
		Point a, b;
	};

	struct Rect
	{
		Point center;
		float width, height;
	};

	struct Circle
	{
		Point center;
		float radius;
	};

	struct Ellipse
	{
		Point center;
		float width, height;
	};

	struct Polyline
	{
		std::vector<Point> vertices;
	};

	struct Polygon
	{
		std::vector<Point> vertices;
	};

	struct Text
	{
		const char *text;
		float fontSize;
	};
}
