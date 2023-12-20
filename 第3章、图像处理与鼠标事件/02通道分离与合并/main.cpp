#include <iostream>
#include <vector>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	vector<Mat> mv;
	Mat dst;

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	split(src, mv);

#if 0 
	imshow("蓝色单通道", mv[0]);
	imshow("绿色单通道", mv[1]);
	imshow("红色单通道", mv[2]);
#endif

	dst = Mat::zeros(src.size(), src.type());
	mv[1] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("蓝色", dst);

	int from_to[] = { 0,2,1,1,2,0 };
	mixChannels(&src, 1, &dst, 1, from_to, 3);
	imshow("mix channels", dst);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
