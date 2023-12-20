#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat dst = Mat::zeros(src.size(), src.type());

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	flip(src, dst, -1); // 0 上下翻转     1 左右翻转     -1 中心翻转

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
