#include <iostream>
#include <vector>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	Mat src = imread("image.jpg", IMREAD_COLOR);
	Mat dst = Mat::zeros(src.size(), src.type());

	int index = 0;

	const vector<string> colormap_str{
		"COLORMAP_AUTUMN",
		"COLORMAP_BONE",
		"COLORMAP_JET",
		"COLORMAP_WINTER",
		"COLORMAP_RAINBOW",
		"COLORMAP_OCEAN",
		"COLORMAP_SUMMER",
		"COLORMAP_SPRING",
		"COLORMAP_COOL",
		"COLORMAP_HSV",//10
		"COLORMAP_PINK",
		"COLORMAP_HOT",
		"COLORMAP_PARULA",
		"COLORMAP_MAGMA",
		"COLORMAP_INFERNO",
		"COLORMAP_PLASMA",
		"COLORMAP_VIRIDIS",
		"COLORMAP_CIVIDIS",
		"COLORMAP_TWILIGHT",
		"COLORMAP_TWILIGHT_SHIFTED",
		"COLORMAP_TURBO",
		"COLORMAP_DEEPGREEN"
	};
	const vector<int> colormap = {
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_JET,
		COLORMAP_WINTER,
		COLORMAP_RAINBOW,
		COLORMAP_OCEAN,
		COLORMAP_SUMMER,
		COLORMAP_SPRING,
		COLORMAP_COOL,
		COLORMAP_HSV,//10
		COLORMAP_PINK,
		COLORMAP_HOT,
		COLORMAP_PARULA,
		COLORMAP_MAGMA,
		COLORMAP_INFERNO,
		COLORMAP_PLASMA,
		COLORMAP_VIRIDIS,
		COLORMAP_CIVIDIS,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED,//20
		COLORMAP_TURBO,
		COLORMAP_DEEPGREEN
	};
	
	int len = colormap.size();

	if (src.empty()) {
		printf("could not load image¡­¡­\n");
		return -1;
	}

	while (true)
	{
		applyColorMap(src, dst, colormap[index++ % len]);

		putText(dst, colormap_str[index++ % len], Point(50, 50), cv::HersheyFonts::FONT_HERSHEY_COMPLEX, 1, (128, 128, 128), 2, cv::LineTypes::LINE_AA);
		if (waitKey(1000) == 27) {
			destroyAllWindows();
			break;
		}

		imshow("src", dst);
	}

	return 0;
}
