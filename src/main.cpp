#include <opencv2/opencv.hpp> 
#include <point.hpp>
#include "pictures.hpp"
#include "algorithm.hpp"

#include <iostream>
#include <string>

#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::vector;
using std::string;
using std::pair;

void SolveProblem(const string& file_name, bool generate_result_image=true) {
	cv::Mat img = cv::imread(file_name);
	cout << "Image was read successfully, rows: " <<
			img.rows << ", columns: " << img.cols << endl;
	Matrix matrix = ToMatrix(img);

	vector<Point> intersections = GetIntersections(matrix);
	const double close_distance = 5;
	intersections = RemoveClosePoints(intersections, close_distance);
	cout << "Intersections number: " << intersections.size() << endl;

	if (generate_result_image) {
		DrawImage("result_image.png", matrix, intersections);
	}
}

int main() {
	cout << "Enter full path to the image:" << endl;
	// example: /home/elisey/1c_task/1c_task/pictures/test_image.png

	string file_name;
	cin >> file_name;
	SolveProblem(file_name);
	return 0;
}
