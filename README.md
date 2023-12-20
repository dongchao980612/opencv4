# OpenCV4快速入门30讲
## 第1章 入门知识
### 00 环境配置与搭建

### 01 图像读取与显示

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
### 02 图像色彩空间转换
```c++
cvtColor(src, gray, COLOR_BGR2HSV); // rgb -> gray
cvtColor(src, hsv, COLOR_BGR2GRAY);// rgb -> hsv [H:0-180 S、V:0-255 ]

imwrite("./gray.png", gray);
imwrite("./hsv.png", hsv);
```

### 03 图像对象的创建与赋值
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
### 04 图像像素的读写操作
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
### 05 图像像素的算术操作
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
### 06 滚动条操作1.0 - 调整图像亮度
```c++
static void on_light(int pos, void* userdata) {
	Mat src = *(Mat*)(userdata);
	Mat dst = Mat::zeros(src.size(), src.type());
	Mat m = Mat::zeros(src.size(), src.type());
	m = Scalar(pos, pos, pos);

	add(src, m, dst);

	imshow(winname, dst);	
}

createTrackbar("light", winname, &light, max_light_value, on_light,&src);
```
07 滚动条操作2.0 - 调整亮度与对比度
```c++
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

createTrackbar("light", winname, &light, max_light_value, on_light, (void*)&src);
createTrackbar("constast", winname, &constast, max_constast_value, on_contrast, (void*)&src);
```
08 键盘响应操作
```c++
while (true)
{
	imshow("键盘响应", dst);
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
```
### Opencv自带颜色表操作
```c++
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
```
## 第3章 图像处理与鼠标事件
### 10 图像像素的逻辑操作
```c++
rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);

imshow("m1", m1);
imshow("m2", m2);

bitwise_and(m1, m2, dst);
imshow("bitwise_and", dst);

bitwise_or(m1, m2, dst);
imshow("bitwise_or", dst);

//bitwise_not(src, m);
m = ~src;
imshow("bitwise_not", m);


bitwise_xor(m1, m2, dst);
imshow("bitwise_xor", dst);
```
### 11 通道分离与合并
```c++
split(src, mv);

#if 0 
imshow("蓝色单通道", mv[0]);
imshow("绿色单通道", mv[1]);
imshow("红色单通道", mv[2]);
#endif

dst = Mat::zeros(src.size(), src.type());
mv[1] = 0;
mv[2] = 0;
merge(mv, dst);
imshow("蓝色", dst);

int from_to[] = { 0,2,1,1,2,0 };
mixChannels(&src, 1, &dst, 1, from_to, 3);
imshow("mix channels", dst);
```
### 12 图像色彩空间转换 - 进阶
```c++
cvtColor(src, hsv, COLOR_BGR2HSV);
inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);

redback= Mat::zeros(src.size(), src.type());
redback = Scalar(40, 40, 250);
bitwise_not(mask, mask);
src.copyTo(redback, mask);

imshow("src", src);
imshow("hsv", hsv);
imshow("mask", mask);
imshow("redback", redback);
```

### 13 图像像素值统计

```c++
// 初始化输出参数
double minVal = 0.0, maxVal = 0.0;
Point minLoc, maxLoc;
Mat mean, stddev;

vector<Mat> mv;

if (src.empty()) {
    printf("could not load image……\n");
    return -1;
}

split(src, mv);
for (int i = 0; i <= src.dims; i++)
{
    // 查找最大值和最小值及其位置
    minMaxLoc(mv[i], &minVal, &maxVal, &minLoc, &maxLoc);

    cout << "Chennel = " << i << ",minv = " << minVal << ", maxv = " << maxVal << endl;
    cout << "Min location: (" << minLoc.x << ", " << minLoc.y << ")" << endl;
    cout << "Max location: (" << maxLoc.x << ", " << maxLoc.y << ")" << endl;
    cout << endl;
}


meanStdDev(src, mean, stddev);
cout << "\n\nmean = " << mean << "\n\nstddev = " << stddev << endl;
```

### 14 图像几何形状绘制

```c++
Rect rect;
rect.x = 30;
rect.y = 40;
rect.width = 100;
rect.height = 200;
rectangle(bg, rect, Scalar(0, 0, 255), -1, LINE_4, 0);

Point p;
p.x = src.cols / 2;
p.y = src.rows / 2;
int r = 100;
circle(bg, p, r, Scalar(0, 255, 255), 1, LINE_8, 0);

line(bg, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height), Scalar(255, 0, 0), 1, LINE_AA, 0);

RotatedRect rrt;
rrt.center = Point(p.x, p.y);
rrt.size = Size(100, 150);
rrt.angle = 90;
ellipse(bg, rrt, Scalar(255, 255, 0), 1, LINE_8);

addWeighted(src, 0.7, bg, 0.3,0, dst);
```



### 15 随机数与随机颜色

```c++
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
```



### 16 多边形填充与绘制

```c++
Point p1(40, 40), p2(80, 80), p3(80, 60), p4(120, 80), p5(120, 60), p6(160, 40);
pts.push_back(p1);
pts.push_back(p2);
pts.push_back(p3);
pts.push_back(p4);
pts.push_back(p5);
pts.push_back(p6);
#if 0
polylines(canvas, pts, true, Scalar(200, 0, 0), 1, LINE_AA, 0);
fillPoly(canvas, pts, Scalar(200, 0, 0), LINE_AA, 0);
#endif // 0
std::vector<std::vector<Point>> contours;

contours.push_back(pts);
// cout << contours.size() << endl;

drawContours(canvas, contours, -1, Scalar(200, 0, 0), -1);
```



### 17 鼠标操作与响应

```c++
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

namedWindow("鼠标绘制矩形", WINDOW_AUTOSIZE);
setMouseCallback("鼠标绘制矩形", on_draw, (void*)(&src));

tmp = src.clone();
```



### 18 图像像素类型转换与归一化

```c++
Mat dst; // Mat type 默认是 0 

cout << src.type() << endl;// CV_8UC3 16 

src.convertTo(src, CV_32F);//转为32位浮点,通道数没有变

cout << src.type() << endl; // CV_32FC3 21

normalize(src, dst, 1, 0, NORM_MINMAX);

cout << dst.type() << endl;  // 21
```



### 19 图像放缩与插值

```c++
Mat dst1 = Mat::zeros(src.size(), src.type());
Mat dst2 = Mat::zeros(src.size(), src.type());

int w = src.cols;
int h = src.rows;

resize(src, dst1, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
imshow("dst1", dst1);

resize(src, dst2, Size(w * 1.5, h * 1.5), 0, 0, INTER_LINEAR);
```



### 20 图像翻转

```c++
flip(src, dst, -1); // 0 上下翻转     1 左右翻转     -1 中心翻转
```

### 21 图像旋转

```c++
int w = src.cols;
int h = src.rows;

Mat M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);
cout << M << endl;

// C++的abs则可以自然支持对整数和浮点数两个版本（实际上还能够支持复数）
double cos = abs(M.at<double>(0, 0));
double sin = abs(M.at<double>(0, 1));

int nw = w * cos + h * sin;
int nh = w * sin + h * cos;

cout << "w = " << w << ", h = " << h << endl;
cout << "nw = " << nw << ", nh = " << nh << endl;

// 新图像的旋转中心
M.at<double>(0, 2) += (nw / static_cast<double>(2) - w / static_cast<double>(2));
M.at<double>(1, 2) += (nh / static_cast<double>(2) - h / static_cast<double>(2));

// warpAffine(src, dst, M, src.size(), INTER_LINEAR, 0, Scalar(0, 200, 0));
warpAffine(src, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(0, 200, 0)); // 重新改变大小
```

## 第4章 视频处理
### 22 视频文件摄像头使用
### 23 视频处理与保存

## 第5章 直方图与卷积

### 24 图像直方图
### 25 二维直方图
### 26 直方图均衡化
### 27 图像卷积操作
### 28 高斯模糊
### 29 高斯双边模糊

## 第6章 案例

### 30 案例：实施人脸检测

> 版权声明：本文为CSDN博主「啦啦啦大赛第大所」的原创文章，原文链接：https://blog.csdn.net/liandanba/article/details/122726576