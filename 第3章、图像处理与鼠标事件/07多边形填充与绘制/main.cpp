#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat canvas = Mat::zeros(src.size(), src.type());
	std::vector<Point> pts;

	if (src.empty()) {
		printf("could not load image¡­¡­\n");
		return -1;
	}

	Point p1(40, 40), p2(80, 80), p3(80, 60), p4(120, 80), p5(120, 60), p6(160, 40);
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
	pts.push_back(p6);
#if 0
	polylines(canvas, pts, true, Scalar(200, 0, 0), 1, LINE_AA, 0);
	fillPoly(canvas, pts, Scalar(200, 0, 0), LINE_AA, 0);
#endif // 0
	std::vector<std::vector<Point>> contours;

	contours.push_back(pts);
	// cout << contours.size() << endl;

	drawContours(canvas, contours, -1, Scalar(200, 0, 0), -1);

	imshow("src", canvas);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
