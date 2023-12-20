#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat dst1 = Mat::zeros(src.size(), src.type());
	Mat dst2 = Mat::zeros(src.size(), src.type());

	if (src.empty()) {
		printf("could not load image¡­¡­\n");
		return -1;
	}

	int w = src.cols;
	int h = src.rows;

	resize(src, dst1, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
	imshow("dst1", dst1);

	resize(src, dst2, Size(w * 1.5, h * 1.5), 0, 0, INTER_LINEAR);
	imshow("dst2", dst2);

	imshow("src", src);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
