#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat hsv, mask,redback;

	if (src.empty()) {
		printf("could not load image¡­¡­\n");
		return -1;
	}

	cvtColor(src, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);

	redback= Mat::zeros(src.size(), src.type());
	redback = Scalar(40, 40, 250);
	bitwise_not(mask, mask);
	src.copyTo(redback, mask);

	imshow("src", src);
	imshow("hsv", hsv);
	imshow("mask", mask);
	imshow("redback", redback);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
