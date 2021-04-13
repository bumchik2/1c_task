#pragma once

#include "point.hpp"
#include "pictures.hpp"

#include <vector>

using std::vector;

double Density(const Matrix& matrix, const Point& point, int r);

bool DensityIsBetween(const Matrix& matrix, const Point& point, int r, 
		double lower, double upper);

bool IsDense(const Matrix& matrix, const Point& point, int r);

double SymmetryCoefficient(const Matrix& matrix, const Point& point, int r);

bool IsSymmetric(const Matrix& matrix, const Point& point, int r);

bool IsLocalDensityMaximum(const Matrix& matrix, const Point& point, 
		const vector<vector<double>>& density_matrix, int r);

bool IsIntersection(const Matrix& matrix, const Point& point,
		const vector<vector<double>>& density_matrix, int r);

vector<Point> GetIntersections(const Matrix& matrix);

vector<Point> RemoveClosePoints(const vector<Point>& points, const double close_distance);
