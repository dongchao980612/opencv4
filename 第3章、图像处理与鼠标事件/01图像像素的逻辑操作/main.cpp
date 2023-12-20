#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat m = Mat::zeros(src.size(), src.type());
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat dst = Mat::zeros(Size(256, 256), CV_8UC3);

	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);

	imshow("m1", m1);
	imshow("m2", m2);

	bitwise_and(m1, m2, dst);
	imshow("bitwise_and", dst);

	bitwise_or(m1, m2, dst);
	imshow("bitwise_or", dst);

	//bitwise_not(src, m);
	m = ~src;
	imshow("bitwise_not", m);


	bitwise_xor(m1, m2, dst);
	imshow("bitwise_xor", dst);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
