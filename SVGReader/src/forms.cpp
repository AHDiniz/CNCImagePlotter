#include "forms.hpp"

#include <cmath>

namespace Forms
{
	const std::vector<Point> &Line::Draw(void)
    {
        std::vector<Point> points;

        float dx = b.x - a.x, dy = b.y - a.y;

        if (dx == 0)
        {
            float iy;
            for (Point current = a; current.y != b.y; current.y += 1)
                points.push_back(current);
        }
        else if (dy == 0)
        {
            float ix;
            for (Point current = a; current.x != b.x; current.x += 1)
                points.push_back(current);
        }
        else
        {
            float ix, iy;
        }

        return points;
    }
}
