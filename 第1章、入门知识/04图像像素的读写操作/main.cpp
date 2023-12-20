#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("image.jpg", IMREAD_COLOR);

	if (src.empty()) {
		printf("could not load image¡­¡­\n");
		return -1;
	}
	
	int w = src.cols;
	int h = src.rows;
	int dims = src.channels();
	cout << "w = " << w << "\th =  " << h << "\tdim = " << dims << endl;
	// w = 789 h =  334 dim = 3
#if 0
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (dims == 1) {
				// »Ò¶ÈÍ¼Ïñ
				int pv = src.at<uchar>(i, j);
				src.at<uchar>(i, j) = 255 - pv;
			}if (dims == 3) {
				// ²ÊÉ«Í¼Ïñ
				Vec3b bgr = src.at<Vec3b>(i, j);
				src.at<Vec3b>(i, j)[0] = 255 - bgr[0];
				src.at<Vec3b>(i, j)[1] = 255 - bgr[1];
				src.at<Vec3b>(i, j)[2] = 255 - bgr[2];

			}
		}
	}
#endif

	for (int i = 0; i < h; i++)
	{
		uchar* current_row = src.ptr< uchar>(i);
		cout << *current_row ;
		for (int j = 0; j < w; j++)
		{
			if (dims == 1) {
				// »Ò¶ÈÍ¼Ïñ
				int pv = *current_row;
				*current_row++ = 255 - pv;
			}if (dims == 3) {
				// ²ÊÉ«Í¼Ïñ
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}

	imshow("ÏñËØ¶ÁÐ´ÑÝÊ¾", src); 

	waitKey(0);

	destroyAllWindows();

	return 0;
}