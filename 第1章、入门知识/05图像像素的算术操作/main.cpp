#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat m = Mat::zeros(src.size(), src.type());
	m = Scalar(50, 50, 50);

	int w = src.cols;
	int h = src.rows;
	int dims = src.channels();


	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	// 加法操作
	Mat dst_plus = Mat::zeros(src.size(), src.type());
	//dst_plus = src + Scalar(50, 50, 50);
	add(src, m, dst_plus);

	// 减法操作
	Mat dst_min = Mat::zeros(src.size(), src.type());
	// dst_min = src - Scalar(50, 50, 50);
	subtract(src, m, dst_min);

	// 乘法操作
	Mat dst_mul = Mat::zeros(src.size(), src.type());
	multiply(src, m, dst_mul);

	// 除法操作
	Mat dst_div = Mat::zeros(src.size(), src.type());
	// dst_div = src / Scalar(5, 5, 5);
	m = Scalar(5, 5, 5);
	divide(src, m, dst_div);

#if 0
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			Vec3b p1 = src.at<Vec3b>(i, j);
			Vec3b p2 = m.at<Vec3b>(i, j);

			dst_mul.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(p1[0] + p2[0]);
			dst_mul.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
			dst_mul.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
		}
	}
#endif

	imshow("加法操作", dst_plus);
	imshow("减法操作", dst_min);
	imshow("乘法操作", dst_mul);
	imshow("除法操作", dst_div);

	waitKey(0);

	destroyAllWindows();

	return 0;
}