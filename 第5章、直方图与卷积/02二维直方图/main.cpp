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

	// 2D 直方图
	Mat hsv, hs_hist;
	cvtColor(src, hsv, COLOR_BGR2HSV);

	int h_bins = 30;
	int s_bins = 32;

	int hist_bins[] = { h_bins, s_bins };

	float h_range[] = { 0, 180 };
	float s_range[] = { 0, 256 };
	const float* hs_ranges[] = { h_range, s_range };

	int hs_channels[] = { 0, 1 };

	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges);

	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);

	int scale = 10;

	//行320 列300
	Mat hist2d_image = Mat::zeros(s_bins * scale, h_bins * scale, CV_8UC3);

	//h30行,s32列，一行一行的绘制矩形
	for (int h = 0; h < h_bins; h++) {
		for (int s = 0; s < s_bins; s++)
		{
			float binVal = hs_hist.at<float>(h, s);//位于横h，列s处的频次

			int intensity = cvRound(binVal * 255 / maxVal);//白色的强度，频次越大，小矩形越接近白色

			Point p1(h * scale, s * scale);
			/*
				矩形左上角的点
			*/
			Point p2((h + 1) * scale - 1, (s + 1) * scale - 1);
			/*
				矩形右下角的点
				-1只是为了不与其他矩形的左上角重合，不-1差异也不大
			*/

			rectangle(hist2d_image, p1, p2, Scalar::all(intensity), -1);
		}
	}

	//灰色的图像不容看出差异，这里我们转换色彩风格
	applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);

	imshow("src", src);
	imshow("H-S Histogram", hist2d_image);


	waitKey(0);

	destroyAllWindows();

	return 0;
}
