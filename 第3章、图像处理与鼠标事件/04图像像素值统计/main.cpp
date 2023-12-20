#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	// 初始化输出参数
	double minVal = 0.0, maxVal = 0.0;
	Point minLoc, maxLoc;
	Mat mean, stddev;

	vector<Mat> mv;

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	split(src, mv);
	for (int i = 0; i <= src.dims; i++)
	{
		// 查找最大值和最小值及其位置
		minMaxLoc(mv[i], &minVal, &maxVal, &minLoc, &maxLoc);

		cout << "Chennel = " << i << ",minv = " << minVal << ", maxv = " << maxVal << endl;
		cout << "Min location: (" << minLoc.x << ", " << minLoc.y << ")" << endl;
		cout << "Max location: (" << maxLoc.x << ", " << maxLoc.y << ")" << endl;
		cout << endl;
	}


	meanStdDev(src, mean, stddev);
	cout << "\n\nmean = " << mean << "\n\nstddev = " << stddev << endl;

	return 0;

}