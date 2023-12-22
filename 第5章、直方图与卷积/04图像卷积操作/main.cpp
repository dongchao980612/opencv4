#include <iostream>
#include <vector>

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
#if 0
	int h = src.rows;
	int w = src.cols;
	Mat result = src.clone();

	//最外面一边我们选择不处理，忽略掉
	for (int row = 1; row < h - 1; row++) {
		for (int col = 1; col < w - 1; col++) {
			// 3x3卷积核
			int sb = src.at<Vec3b>(row, col)[0] + src.at<Vec3b>(row - 1, col - 1)[0] + src.at<Vec3b>(row - 1, col)[0] +
				src.at<Vec3b>(row - 1, col + 1)[0] + src.at<Vec3b>(row, col - 1)[0] + src.at<Vec3b>(row, col + 1)[0] +
				src.at<Vec3b>(row + 1, col - 1)[0] + src.at<Vec3b>(row + 1, col)[0] + src.at<Vec3b>(row + 1, col + 1)[0];

			int sg = src.at<Vec3b>(row, col)[1] + src.at<Vec3b>(row - 1, col - 1)[1] + src.at<Vec3b>(row - 1, col)[1] +
				src.at<Vec3b>(row - 1, col + 1)[1] + src.at<Vec3b>(row, col - 1)[1] + src.at<Vec3b>(row, col + 1)[1] +
				src.at<Vec3b>(row + 1, col - 1)[1] + src.at<Vec3b>(row + 1, col)[1] + src.at<Vec3b>(row + 1, col + 1)[1];

			int sr = src.at<Vec3b>(row, col)[2] + src.at<Vec3b>(row - 1, col - 1)[2] + src.at<Vec3b>(row - 1, col)[2] +
				src.at<Vec3b>(row - 1, col + 1)[2] + src.at<Vec3b>(row, col - 1)[2] + src.at<Vec3b>(row, col + 1)[2] +
				src.at<Vec3b>(row + 1, col - 1)[2] + src.at<Vec3b>(row + 1, col)[2] + src.at<Vec3b>(row + 1, col + 1)[2];
			result.at<Vec3b>(row, col)[0] = sb / 9;
			result.at<Vec3b>(row, col)[1] = sg / 9;
			result.at<Vec3b>(row, col)[2] = sr / 9;
		}
	}
	imshow("conv-demo", result);

#endif

	//二维卷积
	blur(src, dst, Size(3, 3),Point(-1,-1));

	//一维卷积
	// blur(src, dst, Size(13, 1));//行卷积
	// blur(src, dst, Size(1, 13));//列卷积

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
