#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace dnn;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	//文件夹路径
	string pb_file_path = "./opencv_face_detector_uint8.pb";
	string pbtxt_file_path = "./opencv_face_detector.pbtxt";

	//读取以TensorFlow框架格式存储的网络模型
	Net net = readNetFromTensorflow(pb_file_path, pbtxt_file_path);

	if (net.empty()) {
		printf("could not load model……\n");
		return -1;
	}

	//对摄像头进行人脸检测
	VideoCapture capture(0);
	Mat frame;

	while (true) {
		capture.read(frame);//frame为输出，read是将捕获到的视频一帧一帧的传入frame

		if (frame.empty()) {
			break;
		}

		flip(frame, frame, 1);//左右翻转

		//准备深度学习模型需要的数据 （blob-斑点）
		Mat blob = blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		net.setInput(blob);

		//完成推理
		Mat probs = net.forward();

		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

		//解析结果
		for (int i = 0; i < detectionMat.rows; i++) {
			float confidence = detectionMat.at<float>(i, 2);//第三个值 得分
			if (confidence > 0.5) {

				//因为预测来的值为[0,1]范围的数，我们还需要*原图像的宽度和长度
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

				Rect rect(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, rect, Scalar(0, 0, 255), 2, 8, 0);
			}
		}

		imshow("人脸检测", frame);

		if (waitKey(1) == 27) {
			break;
		}
	}

	destroyAllWindows();

	return 0;
}
