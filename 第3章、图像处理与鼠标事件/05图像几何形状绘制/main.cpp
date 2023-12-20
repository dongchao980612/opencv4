#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat bg = Mat::zeros(src.size(), src.type());
	Mat dst = Mat::zeros(src.size(), src.type());
	

	if (src.empty()) {
		printf("could not load image¡­¡­\n");
		return -1;
	}

	Rect rect;
	rect.x = 30;
	rect.y = 40;
	rect.width = 100;
	rect.height = 200;
	rectangle(bg, rect, Scalar(0, 0, 255), -1, LINE_4, 0);

	Point p;
	p.x = src.cols / 2;
	p.y = src.rows / 2;
	int r = 100;
	circle(bg, p, r, Scalar(0, 255, 255), 1, LINE_8, 0);

	line(bg, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height), Scalar(255, 0, 0), 1, LINE_AA, 0);

	RotatedRect rrt;
	rrt.center = Point(p.x, p.y);
	rrt.size = Size(100, 150);
	rrt.angle = 90;
	ellipse(bg, rrt, Scalar(255, 255, 0), 1, LINE_8);

	addWeighted(src, 0.7, bg, 0.3,0, dst);

	imshow("src", src);

	imshow("bg", bg);

	imshow("dst", dst);


	waitKey(0);

	destroyAllWindows();

	return 0;
}