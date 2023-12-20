#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	Mat gray, hsv;
	Mat src = imread("image.jpg", IMREAD_COLOR); // B G R

	if (src.empty()) {
		printf("could not load image¡­¡­\n");
		return -1;
	}


	cvtColor(src, gray, COLOR_BGR2HSV); // rgb -> gray
	cvtColor(src, hsv, COLOR_BGR2GRAY);// rgb -> hsv [H:0-180 S¡¢V:0-255 ]

	imshow("src", src);
	imshow("gray", gray);
	imshow("hsv", hsv);

	imwrite("./gray.png", gray);
	imwrite("./hsv.png", hsv);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
