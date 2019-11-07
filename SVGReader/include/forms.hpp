#pragma once

#include <vector>

/**
 * Geometric forms data definitions
*/

namespace Forms
{
	struct Point
	{
		int x, y;
	};

	struct Line
	{
		Point a, b;
	};

	struct Rect
	{
		Point center;
		int width, height;
	};

	struct Circle
	{
		Point center;
		int radius;
	};

	struct Ellipse
	{
		Point center;
		int width, height;
	};

	struct Polyline
	{
		std::vector<Point> points;
	};

	struct Polygon
	{
		std::vector<Point> points;
	};

	/**
	 * Functions that get a geometric form and transform them in a sequence of points to be drawn
	 * in a sequence of points to be drawn by the arduino plotter
	*/

	const std::vector<Point> &Draw(const Line &l);
	const std::vector<Point> &Draw(const Rect &r);
	const std::vector<Point> &Draw(const Circle &c);
	const std::vector<Point> &Draw(const Ellipse &e);
	const std::vector<Point> &Draw(const Polyline &p);
	const std::vector<Point> &Draw(const Polygon &p);

}
