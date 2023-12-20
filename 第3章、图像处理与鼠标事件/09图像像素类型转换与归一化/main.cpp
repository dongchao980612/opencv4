#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat dst; // Mat type 默认是 0 

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}
	
	cout << src.type() << endl;// CV_8UC3 16 

	src.convertTo(src, CV_32F);//转为32位浮点,通道数没有变

	cout << src.type() << endl; // CV_32FC3 21

	normalize(src, dst, 1, 0, NORM_MINMAX);

	cout << dst.type() << endl;  // 21

	// imshow("src", src);
	imshow("dst", dst);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
