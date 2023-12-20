#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;


const String winname = "调整图像亮度与对比度";

static void on_light(int pos, void* userdata) {
	Mat src = *(Mat*)(userdata);
	Mat dst = Mat::zeros(src.size(), src.type());
	Mat m = Mat::zeros(src.size(), src.type());
	m = Scalar(pos, pos, pos);

	add(src, m, dst);

	imshow(winname, dst);
}

static void on_contrast(int pos, void* userdata) {
	Mat src = *(Mat*)(userdata);
	Mat dst = Mat::zeros(src.size(), src.type());
	Mat m = Mat::zeros(src.size(), src.type());
	m = Scalar(pos, pos, pos);

	double alpha = pos / 100.0;
	addWeighted(src, alpha, m, 0.0, 0.0, dst);

	imshow(winname, dst);
}

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	Mat src = imread("image.jpg", IMREAD_COLOR);

	int light = 50;
	int max_light_value = 100;

	int constast = 100;
	int max_constast_value = 200;

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	namedWindow(winname, WINDOW_AUTOSIZE);
	createTrackbar("light", winname, &light, max_light_value, on_light, (void*)&src);
	createTrackbar("constast", winname, &constast, max_constast_value, on_contrast, (void*)&src);
	//on_light(light, (void*)&src);
	//on_contrast(constast, (void*)&src);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
