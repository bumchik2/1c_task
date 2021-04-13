#include "pictures.hpp"

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

inline bool IsIntense(const cv::Vec3b& color) {
	return color.val[0] + color.val[1] + color.val[2] < 255 * 3 / 2;
}

inline char ToChar(bool a) {
	return a ? '#' : '.';
}

cv::Scalar ToScalar(bool a) {
	return a ? cv::Scalar(0, 0, 0) : cv::Scalar(255, 255, 255);
}

cv::Vec3b ToVec3b(bool a) {
	return a ? cv::Vec3b(0, 0, 0) : cv::Vec3b(255, 255, 255);
}

Matrix ToMatrix(const cv::Mat& image) {
	vector<vector<bool>> answer(image.rows, vector<bool>(image.cols));

	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j) {
			cv::Vec3b color = image.at<cv::Vec3b>(i, j);
			answer[i][j] = IsIntense(color);
		}
	}

	return answer;
}

ostream& operator << (ostream& os, const Matrix& matrix) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			os << ToChar(matrix[i][j]);
		}
		os << endl;
	}
	return os;
}

void DrawDot(cv::Mat& image, const Point& p, int dot_size, 
		const cv::Vec3b& color = cv::Vec3b(0, 0, 255)) {
	const int rows = image.rows;
	const int cols = image.cols;

	int row = p.row;
	int column = p.column;
	for (int i = row - dot_size; i <= row + dot_size; ++i) {
		for (int j = column - dot_size; j <= column + dot_size; ++j) {
			if (IsCorrect(Point{i, j}, rows, cols) && Distance(Point{i, j}, p) <= dot_size) {
				image.at<cv::Vec3b>(i, j) = color;
			}
		}
	}
}

void DrawImage(const string& image_name, const Matrix& matrix,
		const vector<Point>& critical_points = vector<Point>()) {
	// draw image similar to the input image
	cv::Mat image(matrix.size(), matrix[0].size(), CV_8UC3, cv::Scalar(0, 0, 0));
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			image.at<cv::Vec3b>(i, j) = ToVec3b(matrix[i][j]);
		}
	}

	// draw intersections as green dots on the image
	const int dot_size = 0.02 * matrix.size();
	for (int i = 0; i < critical_points.size(); ++i) {
		DrawDot(image, critical_points[i], dot_size, cv::Vec3b(0, 255, 0));
	}

	// draw scan radius size on picture
	DrawDot(image, Point{0, 0}, dot_size);
	const int r = 12;
	// const int r = static_cast<int>(0.05 * matrix.size());
	DrawDot(image, Point{0, r}, dot_size);

	imwrite("../output/" + image_name, image);
	cout << "Result image has been saved in output folder as '" << image_name << "'" << endl;
}
