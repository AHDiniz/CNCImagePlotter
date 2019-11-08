#include "forms.hpp"

#include <cmath>
#include <iostream>

namespace Forms
{
	const std::vector<Point> &Line::Draw(void)
    {
        std::vector<Point> points;

        float dx = b.x - a.x, dy = b.y - a.y;

        if (dx == 0 && dy == 0)
            points.push_back(a);
        else if (dx == 0)
        {
            float iy = (dy > 0) ? 1 : -1;
            for (Point current = a; current.y != b.y; current.y += 1)
                points.push_back(current);
        }
        else if (dy == 0)
        {
            float ix = (dx > 0) ? 1 : -1;
            for (Point current = a; current.x != b.x; current.x += ix)
                points.push_back(current);
        }
        else
        {
            float adx = fabsf32(dx), ady = fabsf32(dy);
            float deno = (adx < ady) ? adx : ady;
            float ix = dx / deno;
            float iy = dy / deno;
            for (Point current = a; current.x != b.x && current.y != b.y;)
            {
                points.push_back(current);
                current.x += ix;
                current.y += iy;
            }
        }

        return points;
    }

    void Line::Print()
    {
        std::cout << "Line: a = (" << a.x << ", " << a.y << "), b = (" << b.x << ", " << b.y << ")" << std::endl;
    }

    const std::vector<Point> &Rect::Draw(void)
    {
        std::vector<Point> points;

        /* Top points */ {

            Point a = {center.x - width / 2, center.y + height / 2};
            Point b = {center.x + width / 2, center.y + height / 2};
            Line l;
            l.a = a; l.b = b;
            for (Point p : l.Draw()) points.push_back(p);
        }

        /* Bottom points */ {

            Point a = {center.x - width / 2, center.y - height / 2};
            Point b = {center.x + width / 2, center.y - height / 2};
            Line l;
            l.a = a; l.b = b;
            for (Point p : l.Draw()) points.push_back(p);
        }

        /* Left points */ {

            Point a = {center.x - width / 2, center.y - height / 2};
            Point b = {center.x - width / 2, center.y + height / 2};
            Line l;
            l.a = a; l.b = b;
            for (Point p : l.Draw()) points.push_back(p);
        }

        /* Right points */ {

            Point a = {center.x + width / 2, center.y - height / 2};
            Point b = {center.x + width / 2, center.y + height / 2};
            Line l;
            l.a = a; l.b = b;
            for (Point p : l.Draw()) points.push_back(p);
        }

        return points;
    }

    void Rect::Print()
    {
        std::cout << "Rect: center = (" << center.x << ", " << center.y << "), width = " << width << "height = " << height << std::endl;
    }

    const std::vector<Point> &Circle::Draw(void)
    {
        std::vector<Point> points;

        for (float angle = 0; angle <= 360; ++angle)
        {
            Point p = {center.x + (radius * cosf(angle)), center.y + (radius * sinf(angle))};
            points.push_back(p);
        }

        return points;
    }

    void Circle::Print()
    {
        std::cout << "Circle: center = (" << center.x << ", " << center.y << "), radius = " << radius << std::endl;
    }

    const std::vector<Point> &Ellipse::Draw(void)
    {
        std::vector<Point> points;

        for (float angle = 0; angle <= 360; ++angle)
        {
            Point p = {center.x + (width * cosf(angle)), center.y + (height * sinf(angle))};
            points.push_back(p);
        }

        return points;
    }

    void Ellipse::Print()
    {
        std::cout << "Rect: center = (" << center.x << ", " << center.y << "), width = " << width << "height = " << height << std::endl;
    }

    const std::vector<Point> &Polyline::Draw(void)
    {
        std::vector<Point> points;

        for (int i = 0; i < vertices.size() - 1; i++)
        {
            Line l;
            l.a = vertices[i]; l.b = vertices[i + 1];
            std::vector<Point> line = l.Draw();
            for (Point p : line) points.push_back(p);
        }

        return points;
    }

    void Polyline::Print()
    {
        std::cout << "Polyline: ";
        for (Point v : vertices)
            std::cout << "(" << v.x << ", " << v.y << ") ";
        std::cout << std::endl;
    }

    const std::vector<Point> &Polygon::Draw(void)
    {
        std::vector<Point> points;

        for (int i = 0; i < vertices.size() - 1; i++)
        {
            Line l;
            l.a = vertices[i]; l.b = vertices[i + 1];
            std::vector<Point> line = l.Draw();
            for (Point p : line) points.push_back(p);
        }

        Line l;
        l.a = vertices[0]; l.b = vertices[vertices.size() - 1];
        std::vector<Point> line = l.Draw();
        for (Point p : line) points.push_back(p);

        return points;
    }

    void Polygon::Print()
    {
        std::cout << "Polygon: ";
        for (Point v : vertices)
            std::cout << "(" << v.x << ", " << v.y << ") ";
        std::cout << std::endl;
    }
}
