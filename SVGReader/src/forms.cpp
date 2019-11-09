#include "forms.hpp"

#include <cmath>
#include <iostream>

namespace Forms
{
	const std::vector<Point> Line::Draw(void)
    {
        std::vector<Point> points;

        points.push_back(a);
        points.push_back(b);

        return points;
    }

    void Line::Print()
    {
        std::cout << "Line: a = (" << a.x << ", " << a.y << "), b = (" << b.x << ", " << b.y << ")" << std::endl;
    }

    const std::vector<Point> Rect::Draw(void)
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
        std::cout << "Rect: center = (" << center.x << ", " << center.y << "), width = " << width << ", height = " << height << std::endl;
    }

    const std::vector<Point> Circle::Draw(void)
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

    const std::vector<Point> Ellipse::Draw(void)
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
        std::cout << "Rect: center = (" << center.x << ", " << center.y << "), width = " << width << ", height = " << height << std::endl;
    }

    const std::vector<Point> Polyline::Draw(void)
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

    const std::vector<Point> Polygon::Draw(void)
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
