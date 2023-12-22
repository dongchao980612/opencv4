#include <iostream>
#include <vector>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src.size(), src.type());

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	equalizeHist(src, dst);

	// 定义参数变量
	const int channels[1] = { 0 };
	Mat hist, hist1; // 256 x 1
	const int bins[1] = { 256 };

	float xrange[2] = { 0,255 };
	const float* ranges[1] = { xrange };

	calcHist(&src, 1, channels, Mat(), hist, 1, bins, ranges);
	calcHist(&dst, 1, channels, Mat(), hist1, 1, bins, ranges);

	// 显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]); // 2

	Mat histImage = Mat::zeros(Size(hist_w, hist_h), CV_8UC3);
	histImage = Scalar(255, 255, 255);

	// 归一化直方图数据为指定范围
	normalize(hist, hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(hist1, hist1, 0, hist_h, NORM_MINMAX, -1, Mat());

	// 绘制直方图曲线
	for (int i = 0; i < 254; i++) {

		Point p01(bin_w * i, hist_h - cvRound(hist.at<float>(i)));
		Point p02(bin_w * i + 1, hist_h - cvRound(hist.at<float>(i + 1)));


		Point p11(bin_w * i, hist_h - cvRound(hist1.at<float>(i)));
		Point p12(bin_w * i + 1, hist_h - cvRound(hist1.at<float>(i + 1)));

		line(histImage, p01, p02, Scalar(255, 0, 0), 1, 8, 0);
		line(histImage, p11, p12, Scalar(255, 255, 0), 1, 8, 0);
	}

	imshow("直方图", histImage);

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
