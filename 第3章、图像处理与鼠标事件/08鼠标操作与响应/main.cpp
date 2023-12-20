#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Point sp(-1, -1), ep(-1, -1);
Mat tmp;
static void on_draw(int event, int x, int y, int flags, void* userdata) {
	Mat src = *((Mat*)userdata);
	Mat bg = Mat::zeros(src.size(), src.type());

	if (event == EVENT_LBUTTONDOWN) {
		sp.x = x;
		sp.y = y;
		cout << "起点：(" << sp.x << ", " << sp.y << ") -> ";
	}
	else if (event == EVENT_LBUTTONUP) {
		ep.x = x;
		ep.y = y;

		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;

		cout << "终点：(" << ep.x << ", " << ep.y << ")" << "\tdx = " << dx << ", dy = " << dy << endl;
		if (dx > 0 || dy > 0) {
			Rect rect(sp.x, sp.y, dx, dy);
			tmp.copyTo(src);
			imshow("ROI区域", src(rect));
			rectangle(src, rect, Scalar(0, 0, 255), 1, LINE_AA, 0);
			imshow("鼠标绘制矩形", src);

			sp.x = -1;
			sp.y = -1;
		}
	}
	else if (event == EVENT_MOUSEMOVE) {
		// 保证鼠标被按下
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;

			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
		
			if (dx > 0 || dy > 0) {
				Rect rect(sp.x, sp.y, dx, dy);
				tmp.copyTo(src);
				rectangle(src, rect, Scalar(0, 0, 255), 1, LINE_AA, 0);
				imshow("鼠标绘制矩形", src);
			}
		}
	}
}
int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);

	if (src.empty()) {
		printf("could not load image……\n");
		return -1;
	}

	namedWindow("鼠标绘制矩形", WINDOW_AUTOSIZE);
	setMouseCallback("鼠标绘制矩形", on_draw, (void*)(&src));

	tmp = src.clone();

	imshow("鼠标绘制矩形", src);

	waitKey(0);

	destroyAllWindows();

	return 0;
}
