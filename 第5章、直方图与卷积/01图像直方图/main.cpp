#include <iostream>
#include <vector>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	// 三通道分离
	std::vector<Mat> bgr;
	split(src, bgr);

	// 定义参数变量
	const int channels[1] = { 0 };
	Mat b_hist, g_hist, r_hist; // 256 x 1
	const int bins[1] = { 256 };

	float xrange[2] = { 0,255 };
	const float* ranges[1] = { xrange };

	// 计算Blue,Green,Red三通道各自的直方图
	calcHist(&bgr[0], 1, channels, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr[1], 1, channels, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr[2], 1, channels, Mat(), r_hist, 1, bins, ranges);


	// 显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	// cout << bin_w << endl;// 2
	Mat histImage = Mat::zeros(Size(hist_w, hist_h), CV_8UC3);

	// 归一化直方图数据为指定范围
	normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

	// 绘制直方图曲线
	for (int i = 0; i < 254; i++) {
		/*
		第一个点横向坐标：bin_w*i: 即 512/256 再 * i
		第二个点纵向坐标：直方图纵高 - 根据直方图纵高归一化后的频次，即为纵向坐标
			当频次很低时，减的少，就靠下，反之靠上
		*/

		Point p01(bin_w * i, hist_h - cvRound(b_hist.at<float>(i)));
		Point p02(bin_w * i + 1, hist_h - cvRound(b_hist.at<float>(i + 1)));

		Point p11(bin_w * i, hist_h - cvRound(g_hist.at<float>(i)));
		Point p12(bin_w * i + 1, hist_h - cvRound(g_hist.at<float>(i + 1)));

		Point p21(bin_w * i, hist_h - cvRound(r_hist.at<float>(i)));
		Point p22(bin_w * i + 1, hist_h - cvRound(r_hist.at<float>(i + 1)));


		line(histImage, p01, p02, Scalar(255, 0, 0), 1, 8, 0);
		line(histImage, p11, p12, Scalar(0, 255, 0), 1, 8, 0);
		line(histImage, p21, p22, Scalar(0, 0, 255), 1, 8, 0);

	}

	imshow("直方图", histImage);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
