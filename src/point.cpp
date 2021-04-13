#include "point.hpp"

#include <cmath>
#include <iostream>

using std::ostream;

ostream& operator << (ostream& os, const Point& p) {
	os << '(' << p.row << ", " << p.column << ')';
	return os;
}

bool operator == (const Point& p1, const Point& p2) {
	return p1.row == p2.row && p1.column == p2.column;
}

bool IsCorrect(const Point& p, int rows, int cols) {
	return 0 <= p.row && p.row < rows && 0 < p.column && p.column < cols;
}

Point& Point::operator += (const Point& other) {
	row += other.row;
	column += other.column;
	return *this;
}

Point& Point::operator -= (const Point& other) {
	row -= other.row;
	column -= other.column;
	return *this;
}

Point& Point::operator *= (double d) {
	row *= d;
	column *= d;
	return *this;
}

Point operator + (const Point& p1, const Point& p2) {
	return Point{p1.row + p2.row, p1.column + p2.column};
}

Point operator - (const Point& p1, const Point& p2) {
	return Point{p1.row - p2.row, p1.column - p2.column};
}

Point operator * (const Point& p, double d) {
	return Point{static_cast<int>(p.row * d), static_cast<int>(p.column * d)};
}

double Length(const Point& p) {
	return sqrt(p.row * p.row + p.column * p.column);
}

double Distance(const Point& p1, const Point& p2) {
	return Length(p1 - p2);
}
