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

	struct Form
	{
		virtual const std::vector<Point> Draw(void) = 0;
		virtual void Print(void) = 0; // Debug only
	};

	struct Line : public Form
	{
		Point a, b;

		const std::vector<Point> Draw(void) override;
		void Print() override;
	};

	struct Rect : public Form
	{
		Point center;
		float width, height;

		const std::vector<Point> Draw(void) override;
		void Print() override;
	};

	struct Circle : public Form
	{
		Point center;
		float radius;

		const std::vector<Point> Draw(void) override;
		void Print() override;
	};

	struct Ellipse : public Form
	{
		Point center;
		float width, height;

		const std::vector<Point> Draw(void) override;
		void Print() override;
	};

	struct Polyline : public Form
	{
		std::vector<Point> vertices;

		const std::vector<Point> Draw(void) override;
		void Print() override;
	};

	struct Polygon : public Form
	{
		std::vector<Point> vertices;

		const std::vector<Point> Draw(void) override;
		void Print() override;
	};

	// struct Text : public Form
	// {
	// 	const char *text;
	// 	float fontSize;

	// 	const std::vector<Point> Draw(void) override;
	// 	void Print() override;
	// };
}
