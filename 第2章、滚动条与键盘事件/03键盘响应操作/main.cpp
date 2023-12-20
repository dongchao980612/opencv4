#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat dst = Mat::zeros(src.size(), src.type());

	int ch = 0;

	if (src.empty()) {
		printf("could not load image°≠°≠\n");
		return -1;
	}

	while (true)
	{
		imshow("º¸≈ÃœÏ”¶", dst);
		imshow("src", src);

		ch = waitKey(1);
		// cout << ch <<  endl;

		if (ch == 49) {
			cvtColor(src, dst, COLOR_BGR2GRAY);
		}

		if (ch == 50) {
			cvtColor(src, dst, COLOR_BGR2HSV);
		}

		if (ch == 51) {
			dst = Scalar(50, 50, 50);
			add(src, dst, dst);
		}

		if (ch == 27) {
			destroyAllWindows();
			break;
		}	
	}

	return 0;
}
