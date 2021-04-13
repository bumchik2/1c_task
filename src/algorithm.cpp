#include "algorithm.hpp"

#include <iostream>

using std::cout;
using std::endl;

double Density(const Matrix& matrix, const Point& point, int r) {
	int total_points = 0;
	int black_points = 0;

	const int rows = matrix.size();
	const int cols = matrix[0].size();

	for (int i = point.row - r; i <= point.row + r; ++i) {
		for (int j = point.column - r; j <= point.column + r; ++j) {
			if (!IsCorrect(Point{i, j}, rows, cols) || Distance(point, Point{i, j}) > r) {
				continue;
			}

			++total_points;
			if (matrix[i][j]) {
				++black_points;
			}
		}
	}

	return static_cast<double>(black_points) / total_points;
}

bool DensityIsBetween(const Matrix& matrix, const Point& point, int r, 
		double lower, double upper) {
	double density = Density(matrix, point, r);
	return lower < density && density < upper;
}

bool IsDense(const Matrix& matrix, const Point& point, int r) {
	const double high_density = 0.5;
	return DensityIsBetween(matrix, point, r, high_density, 1);
}


double SymmetryCoefficient(const Matrix& matrix, const Point& point, int r) {
	int total_points = 0;
	int symmetric_points = 0;

	const int rows = matrix.size();
	const int cols = matrix[0].size();

	for (int i = point.row - r; i <= point.row + r; ++i) {
		for (int j = point.column - r; j <= point.column + r; ++j) {
			if (!IsCorrect(Point{i, j}, rows, cols) || Length(point - Point{i, j}) > r) {
				continue;
			}

			Point current_point = Point{i, j};
			Point symmetric_point = point * 2 - current_point;
			if (IsCorrect(symmetric_point, rows, cols)) {
				++total_points;
				if (matrix[current_point.row][current_point.column] ==
						matrix[symmetric_point.row][symmetric_point.column]) {
					++symmetric_points;
				}
			}

		}
	}

	return static_cast<double>(symmetric_points) / total_points;
}

bool IsSymmetric(const Matrix& matrix, const Point& point, int r) {
	const double normal_symmetry_coefficient = 0.9;
	return SymmetryCoefficient(matrix, point, r) > normal_symmetry_coefficient;
}

bool IsLocalDensityMaximum(const Matrix& matrix, const Point& point, 
		const vector<vector<double>>& density_matrix, int r) {
	const int rows = matrix.size();
	const int cols = matrix[0].size();

	double density = density_matrix[point.row][point.column];

	for (int i = point.row - r; i <= point.row + r; ++i) {
		for (int j = point.column - r; j <= point.column + r; ++j) {
			if (!IsCorrect(Point{i, j}, rows, cols) || Length(point - Point{i, j}) > r) {
				continue;
			}

			if (density_matrix[i][j] > density) {
				return false;
			}
		}
	}
	return true;
}

bool IsIntersection(const Matrix& matrix, const Point& point,
		const vector<vector<double>>& density_matrix, int r) {
	return matrix[point.row][point.column] &&
			IsLocalDensityMaximum(matrix, point, density_matrix, r) && 
			DensityIsBetween(matrix, point, r, 0.3, 0.5);
}

vector<Point> GetIntersections(const Matrix& matrix) {
	vector<Point> answer;
	vector<vector<double>> density_matrix(matrix.size(), vector<double>(matrix[0].size()));

	const int rows = matrix.size();
	const int cols = matrix[0].size();

	const int r = 15;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			density_matrix[i][j] = Density(matrix, Point{i, j}, r);
		}
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			Point point{i, j};
			if (IsIntersection(matrix, point, density_matrix, r)) {
				answer.push_back(point);
			}
		}
	}
	return answer;
}

vector<Point> RemoveClosePoints(const vector<Point>& points, const double close_distance) {
	vector<Point> answer;
	vector<bool> to_delete(points.size(), false);

	for (int i = 0; i < points.size(); ++i) {
		for (int j = i + 1; j < points.size(); ++j) {
			if (Distance(points[i], points[j]) < close_distance) {
				to_delete[j] = true;
			}
		}
	}

	for (int i = 0; i < points.size(); ++i) {
		if (!to_delete[i]) {
			answer.push_back(points[i]);
		}
	}

	return answer;
}
