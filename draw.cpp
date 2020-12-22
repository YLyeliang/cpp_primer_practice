#include <iostream>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;


Rect g_rectangle;
bool g_bDrawing = false;
RNG g_rng(12345);
Point g_nCurrPoint;
int g_nThick = 0, g_nBlue = 255, g_nGreen = 255, g_nRed = 0;

/*注意：不能在毁掉函数中写入未初始化的矩阵类，所以需要用时，需要写一个标志位，然后再在while(1)循环内使用*/
void onMouse(int event, int x, int y, int flag, void *param)
{
    Mat &img = *(cv::Mat*)param;

    switch (event)
    {
        //移动鼠标的时候
        case EVENT_MOUSEMOVE:
        {
            g_nCurrPoint = Point(x, y);
        }
            break;
            //点击鼠标左键时
        case EVENT_LBUTTONDOWN:
        {
            g_bDrawing = true;
            g_nCurrPoint = Point(x, y);
        }
            break;
            //松开鼠标左键时
        case EVENT_LBUTTONUP:
        {
            g_bDrawing = false;
        }
            break;
    }
}

int main() {
    Mat srcImage(600, 800, CV_8UC3);
    Mat tempImage;

    srcImage.copyTo(tempImage);
    srcImage = Scalar::all(0);

    namedWindow("【鼠标事件窗口】", 0);
    setMouseCallback("【鼠标事件窗口】", onMouse, (void *) &srcImage);

    namedWindow("【滚动条窗口】", 0);
    createTrackbar("thick", "【滚动条窗口】", &g_nThick, 100, 0);
    createTrackbar("Blue", "【滚动条窗口】", &g_nBlue, 255, 0);
    createTrackbar("Green", "【滚动条窗口】", &g_nGreen, 255, 0);
    createTrackbar("Red", "【滚动条窗口】", &g_nRed, 255, 0);

    char key;
    while (1) {
        if (g_bDrawing) {
            circle(srcImage, g_nCurrPoint, 0, Scalar(g_nBlue, g_nGreen, g_nRed), g_nThick + 1);
        }

        imshow("【鼠标事件窗口】", srcImage);

        key = waitKey(1);
        if (key == 27)
            break;

        if (key == '1')
            srcImage = Scalar::all(0);

        /*DrawRectangle(srcImage, g_rectangle);
        imshow(WINDOW_NAME, srcImage);
        if (waitKey(10) == 27)
        break;*/
    }

    return 0;
}
