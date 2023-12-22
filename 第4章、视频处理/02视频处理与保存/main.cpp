#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	VideoCapture capture("demo.mp4");

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int frame_count = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);

	VideoWriter  writer("demo_saved.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);

	cout << "frame_width:" << frame_width << endl;
	cout << "frame_height:" << frame_height << endl;
	cout << "frame_count:" << frame_count << endl;
	cout << "fps:" << fps << endl;


	Mat frame;
	int count = 1;
	while (true)
	{
		capture.read(frame);
		if (frame.empty()) {
			cout << "frame.empty()" << endl;
			break;
		}

		// namedWindow("src", WINDOW_FREERATIO);
		// imshow("src", frame);
		writer.write(frame);

		// cout << "save [" << count++ << "," << frame_count << "]..." << endl;

		if (waitKey(1) == 27) {
			break; // ÍË³ö
		}
	}

	capture.release();
	writer.release();

	destroyAllWindows();


	return 0;
}
