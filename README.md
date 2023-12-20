# OpenCV4快速入门30讲
## 第1章 入门知识
00 环境配置与搭建
01 图像读取与显示
```c++
Mat src = imread("image.jpg", IMREAD_COLOR);

if (src.empty()) {
	printf("could not load image……\n");
	return -1;
}

namedWindow("输入窗口", WINDOW_FREERATIO);

imshow("输入窗口", src);

waitKey(0);

destroyAllWindows();
```
02 图像色彩空间转换

```c++
cvtColor(src, gray, COLOR_BGR2HSV); // rgb -> gray
cvtColor(src, hsv, COLOR_BGR2GRAY);// rgb -> hsv [H:0-180 S、V:0-255 ]

imwrite("./gray.png", gray);
imwrite("./hsv.png", hsv);
```

03 图像对象的创建与赋值
```c++
Mat src = imread("image.jpg", IMREAD_COLOR);
Mat m1, m2, m3, m4, m5, m6;

if (src.empty()) {
printf("could not load image……\n");
return -1;
}

m1 = src.clone();

src.copyTo(m2);

// 创建空白图像
/*
CV_8UC1 8 8 1 0 16
CV_8UC1 8 8 3 0 0
*/
m3 = Mat::zeros(Size(280, 280), CV_8UC3);
// m3 = Mat::ones(Size(8, 8), CV_8UC1); // CV_8UC1 -> error 

//m3 = 127; // 只有第一个通道是27
m3 = Scalar(0, 0, 0);// B G R

// cout << m3 << endl;
cout << m3.cols << " " << m3.rows << " " << m3.channels() << endl;
cout << m3.depth() << " " << m3.type() << endl; 

m4 = m3;
m4 = Scalar(255, 0, 0);

m5 = m3.clone();
m5 = Scalar(255, 255, 0);

m3.copyTo(m6);
m5 = Scalar(0, 255, 255);
```
04 图像像素的读写操作
```c++
// 元素
for (int i = 0; i < h; i++)
{
	for (int j = 0; j < w; j++)
	{
		if (dims == 1) {
			// 灰度图像
			int pv = src.at<uchar>(i, j);
			src.at<uchar>(i, j) = 255 - pv;
		}if (dims == 3) {
			// 彩色图像
			Vec3b bgr = src.at<Vec3b>(i, j);
			src.at<Vec3b>(i, j)[0] = 255 - bgr[0];
			src.at<Vec3b>(i, j)[1] = 255 - bgr[1];
			src.at<Vec3b>(i, j)[2] = 255 - bgr[2];

		}
	}
}
// 指针
for (int i = 0; i < h; i++)
{
	uchar* current_row = src.ptr< uchar>(i);
	cout << *current_row ;
	for (int j = 0; j < w; j++)
	{
		if (dims == 1) {
			// 灰度图像
			int pv = *current_row;
			*current_row++ = 255 - pv;
		}if (dims == 3) {
			// 彩色图像
			*current_row++ = 255 - *current_row;
			*current_row++ = 255 - *current_row;
			*current_row++ = 255 - *current_row;
		}
	}
}
```
05 图像像素的算术操作
```c++
// 遍历法
for (int i = 0; i < h; i++)
{
	for (int j = 0; j < w; j++)
	{
		Vec3b p1 = src.at<Vec3b>(i, j);
		Vec3b p2 = m.at<Vec3b>(i, j);

		dst_mul.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(p1[0] * p2[0]);
		dst_mul.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(p1[1] * p2[1]);
		dst_mul.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(p1[2] * p2[2]);
	}
}

// API法
// 加法操作
Mat dst_plus = Mat::zeros(src.size(), src.type());
//dst_plus = src + Scalar(50, 50, 50);
add(src, m, dst_plus);

// 减法操作
Mat dst_min = Mat::zeros(src.size(), src.type());
// dst_min = src - Scalar(50, 50, 50);
subtract(src, m, dst_min);

// 乘法操作
Mat dst_mul = Mat::zeros(src.size(), src.type());
multiply(src, m, dst_mul);

// 除法操作
Mat dst_div = Mat::zeros(src.size(), src.type());
// dst_div = src / Scalar(5, 5, 5);
m = Scalar(5, 5, 5);
divide(src, m, dst_div);
```

## 第2章 滚动条与键盘事件
06 滚动条操作1.0 - 调整图像亮度
07 滚动条操作2.0 - 调整亮度与对比度
08 键盘响应操作
09 Opencv自带颜色表操作

## 第3章 图像处理与鼠标事件

10 图像像素的逻辑操作
11 通道分离与合并
12 图像色彩空间转换 - 进阶
13 图像像素值统计
14 图像几何形状绘制
15 随机数与随机颜色
16 多边形填充与绘制
17 鼠标操作与响应
18 图像像素类型转换与归一化
19 图像放缩与插值
20 图像翻转
21 图像旋转

## 第4章 视频处理
22 视频文件摄像头使用
23 视频处理与保存

## 第5章 直方图与卷积

24 图像直方图
25 二维直方图
26 直方图均衡化
27 图像卷积操作
28 高斯模糊
29 高斯双边模糊

## 第6章 案例

30 案例：实施人脸检测

> 版权声明：本文为CSDN博主「啦啦啦大赛第大所」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
> 原文链接：https://blog.csdn.net/liandanba/article/details/122726576