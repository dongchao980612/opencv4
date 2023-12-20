#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	// 参数1 图片路径
	// 参数2 色彩标志（默认为1，即彩色图像）
	// IMREAD_COLOR    彩色图像
	// IMREAD_GRAYSCALE 灰度图
	// IMREAD_UNCHANGED 透明通
	Mat src = imread("image.jpg", IMREAD_COLOR);

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	namedWindow("输入窗口", WINDOW_FREERATIO);

	// 参数1 窗口名称
	// 参数2 输出对象
	imshow("输入窗口", src);

	//参数1 等待时间（ms）规定0为永远
	waitKey(0);

	// 销毁所有窗口
	destroyAllWindows();

	return 0;
}
