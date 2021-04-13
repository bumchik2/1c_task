#pragma once

#include <opencv2/opencv.hpp>
#include "point.hpp"

#include <string>
#include <iostream>

using std::ostream;
using std::string;
using std::vector;

using Matrix = vector<vector<bool>>;

bool IsCorrect(const Point& p, int rows, int cols);

inline bool IsIntense(const cv::Vec3b& color);

inline char ToChar(bool a);
cv::Scalar ToScalar(bool a);
cv::Vec3b ToVec3b(bool a);

Matrix ToMatrix(const cv::Mat& image);

ostream& operator << (ostream& os, const Matrix& matrix);

void DrawDot(cv::Mat& image, const Point& p, int dot_size, 
		const cv::Vec3b& color);

void DrawImage(const string& image_name, const Matrix& matrix,
		const vector<Point>& critical_points);
