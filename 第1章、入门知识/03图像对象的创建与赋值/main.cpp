#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat m1, m2, m3, m4, m5, m6;

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	m1 = src.clone();

	src.copyTo(m2);

	// 创建空白图像
	/*
	CV_8UC1 8 8 1 0 16
	CV_8UC1 8 8 3 0 0
	*/
	m3 = Mat::zeros(Size(280, 280), CV_8UC3);
	// m3 = Mat::ones(Size(8, 8), CV_8UC1); // CV_8UC1 -> error 

	//m3 = 127; // 只有第一个通道是27
	m3 = Scalar(0, 0, 0);// B G R

	// cout << m3 << endl;
	cout << m3.cols << " " << m3.rows << " " << m3.channels() << endl;
	cout << m3.depth() << " " << m3.type() << endl; 

	m4 = m3;
	m4 = Scalar(255, 0, 0);

	m5 = m3.clone();
	m5 = Scalar(255, 255, 0);

	m3.copyTo(m6);
	m5 = Scalar(0, 255, 255);


	imshow("m3", m3); // 
	imshow("m4", m4); // 与m3相同
	imshow("m5", m5); // 与m3不同
	imshow("m6", m6); // 与m3不同

	waitKey(0);

	destroyAllWindows();

	return 0;
}
