#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat canvas = Mat::zeros(src.size(), src.type());
	int w = canvas.cols;
	int h = canvas.rows;

	RNG rng(12345);

	while (true) {
		int x1 = rng.uniform(0, w);
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);
		int y2 = rng.uniform(0, h);

		int r= rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int b = rng.uniform(0, 255);

		canvas = Scalar(0, 0, 0);//
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(r, g, b), 1, LINE_AA, 0);

		imshow("dst", canvas);

		if (waitKey(10) == 27) {
			destroyAllWindows();
			break;
		}
	}

	return 0;
}