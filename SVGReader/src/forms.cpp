#include "forms.hpp"

#include <cmath>

namespace Forms
{
	const std::vector<Point> &Draw(const Line &l)
	{
		std::vector<Point> result;

		int dx = l.b.x - l.a.x, dy = l.b.y - l.a.y;
		int commonDen = (abs(dx) < abs(dy)) ? abs(dx) : abs(dy);
		float ix, iy;
		
		if (commonDen != 0)
		{
			ix = (float)dx / commonDen;
			iy = (float)dy / commonDen;
		}
		else
		{
			ix = (dx == 0) ? 0 : 1;
			iy = (dy == 0) ? 0 : 1;
		}

		for (Point current = l.a; abs(current.x) <= abs(l.b.x) && abs(current.y) <= abs(l.b.y); )
		{
			result.push_back(current);
			current.x += ix;
			current.y += iy;
		}

		return result;
	}

	const std::vector<Point> &Draw(const Rect &r)
	{
		std::vector<Point> result;

		/* Draw top line */ {

			Point a = { (r.center.x - r.width), (r.center.y + r.height) };
			Point b = { (r.center.x + r.width), (r.center.y + r.height) };
			const Line l = { a, b };

			const std::vector<Point> points = Draw(l);
			for (Point p : points)
				result.push_back(p);
		}

		/* Draw right line */ {

			Point a = { (r.center.x + r.width), (r.center.y - r.height) };
			Point b = { (r.center.x + r.width), (r.center.y + r.height) };
			Line l = { a, b };

			const std::vector<Point> points = Draw(l);
			for (Point p : points)
				result.push_back(p);
		}

		/* Draw bottom line */ {

			Point a = { (r.center.x - r.width), (r.center.y - r.height) };
			Point b = { (r.center.x + r.width), (r.center.y - r.height) };
			Line l = { a, b };

			const std::vector<Point> points = Draw(l);
			for (Point p : points)
				result.push_back(p);
		}

		/* Draw left line */ {

			Point a = { (r.center.x - r.width), (r.center.y - r.height) };
			Point b = { (r.center.x - r.width), (r.center.y + r.height) };
			Line l = { a, b };

			const std::vector<Point> points = Draw(l);
			for (Point p : points)
				result.push_back(p);
		}

		return result;
	}

	const std::vector<Point> &Draw(const Circle &c)
	{
		std::vector<Point> result;

		for (int i = 0; i < 360; ++i)
		{
			Point current = { (c.center.x + c.radius * cos(i)), (c.center.y + c.radius * sin(i)) };
			result.push_back(current);
		}

		return result;
	}

	const std::vector<Point> &Draw(const Ellipse &e)
	{
		std::vector<Point> result;

		for (int i = 0; i < 360; ++i)
		{
			Point current = { (e.center.x + e.width * cos(i)), (e.center.y + e.height * sin(i)) };
			result.push_back(current);
		}

		return result;
	}

	const std::vector<Point> &Draw(const Polyline &p)
	{
		std::vector<Point> result;

		for (int i = 0; i < p.points.size() - 1; ++i)
		{
			Line l = { p.points[i], p.points[i + 1] };
			for (Point point : Draw(l))
				result.push_back(point);
		}

		return result;
	}

	const std::vector<Point> &Draw(const Polygon &p)
	{
		std::vector<Point> result;

		for (int i = 0; i < p.points.size() - 1; ++i)
		{
			Line l = { p.points[i], p.points[i + 1] };
			for (Point point : Draw(l))
				result.push_back(point);
		}

		Line l = { p.points[p.points.size() - 1], p.points[0] };
		for (Point point : Draw(l))
			result.push_back(point);

		return result;
	}
}
