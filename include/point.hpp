#pragma once

#include <iostream>

using std::ostream;

struct Point {
	int row;
	int column;

	Point& operator += (const Point&);
	Point& operator -= (const Point&);
	Point& operator *= (double);
};

ostream& operator << (ostream& os, const Point& p);
bool operator == (const Point& p1, const Point& p2);
bool IsCorrect(const Point& p, int rows, int cols);

Point operator + (const Point& p1, const Point& p2);
Point operator - (const Point& p1, const Point& p2);
Point operator * (const Point& p, double d);

double Length(const Point& p);
double Distance(const Point& p1, const Point& p2);
