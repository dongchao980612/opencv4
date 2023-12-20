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

	int w = src.cols;
	int h = src.rows;

	Mat M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);
	cout << M << endl;

	// C++的abs则可以自然支持对整数和浮点数两个版本（实际上还能够支持复数）
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));

	int nw = w * cos + h * sin;
	int nh = w * sin + h * cos;

	cout << "w = " << w << ", h = " << h << endl;
	cout << "nw = " << nw << ", nh = " << nh << endl;

	// 新图像的旋转中心
	M.at<double>(0, 2) += (nw / static_cast<double>(2) - w / static_cast<double>(2));
	M.at<double>(1, 2) += (nh / static_cast<double>(2) - h / static_cast<double>(2));

	// warpAffine(src, dst, M, src.size(), INTER_LINEAR, 0, Scalar(0, 200, 0));
	warpAffine(src, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(0, 200, 0));

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
