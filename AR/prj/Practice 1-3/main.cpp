#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img = imread("../data/ryan.jpg");
	Mat img2 = imread("../data/windows.jpg");
	Mat roi = img2(Rect(100, 100, img.cols, img.rows));

	img.copyTo(roi);
	imshow("ryan",img);
	imshow("windows", img2);
	waitKey();
}
