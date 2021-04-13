#include "test_runner.hpp"
#include "point.hpp"

void TestEqual() {
	AssertEqual(Point{1, 1}, Point{1, 1});
	Assert(!(Point{1, 1} == Point{1, 2}), "(1, 1) != (1, 2)");
}

void TestPointSum() {
	Point p{1, 1};
	p += Point{2, 4};
	AssertEqual(p, Point{3, 5});
	AssertEqual(Point{1, 2} + Point{2, -1}, Point{3, 1});
}

void TestPointDiff() {
	Point p{1, 1};
	p -= Point{2, 4};
	AssertEqual(p, Point{-1, -3});
	AssertEqual(Point{1, 2} - Point{2, -1}, Point{-1, 3});
}

void TestPointMultiplyByNum() {
	Point p{2, 3};
	p *= 2;
	AssertEqual(p, Point{4, 6});
	AssertEqual(Point{1, 3} * 3, Point{3, 9});
}

void TestLength() {
	AssertEqual(Length(Point{3, 4}), 5);
}

void TestDistance() {
	AssertEqual(Distance(Point{2, 3}, Point{-1, -1}), 5);
}

void TestIsCorrect() {
	AssertEqual(IsCorrect(Point{1, 1}, 2, 2), true);
	AssertEqual(IsCorrect(Point{1, 1}, 2, 1), false);
}

void RunTests() {
	TestRunner test_runner;
	test_runner.RunTest(TestEqual, "test point operator equal");
	test_runner.RunTest(TestPointSum, "test point sum");
	test_runner.RunTest(TestPointDiff, "test point diff");
	test_runner.RunTest(TestPointMultiplyByNum, "test point multiply by number");
	test_runner.RunTest(TestLength, "test length");
	test_runner.RunTest(TestDistance, "test distance");
	test_runner.RunTest(TestIsCorrect, "test is correct");
}
