#pragma once

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

	/**
	 * Functions that get a geometric form and transform them in a sequence of points to be drawn
	 * in a sequence of points to be drawn by the arduino plotter
	*/

	const Point *Draw(const Line &l);
	const Point *Draw(const Rect &r);
	const Point *Draw(const Circle &c);
}
