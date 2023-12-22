#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	VideoCapture capture("demo.mp4");

	Mat frame;

	while (true)
	{
		capture.read(frame);
		if (frame.empty()) {
			cout << "frame.empty()" << endl;
			break;
		}
		Mat gray = Mat::zeros(frame.size(), frame.type());
		Mat hsv = Mat::zeros(frame.size(), frame.type());
		cvtColor(frame, gray, COLOR_BGR2HSV);
		cvtColor(frame, hsv, COLOR_BGR2GRAY);

		// flip(frame, frame, 1);

		imshow("gray", gray);
		imshow("hsv", hsv);
		imshow("src", frame);
		if (waitKey(10) == 27) {
			break; // ÍË³ö
		}
	}
	capture.release();

	destroyAllWindows();


	return 0;
}
