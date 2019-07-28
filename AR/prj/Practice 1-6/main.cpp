#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

const string dataPath = "../data/";

int main(int argc, char** argv)
{
	VideoCapture capture(0);
	Mat frame;
	int num = 1;
	//capture.read(frame);
	while (true)
	{
		capture >> frame;
		imwrite(dataPath + "out/" + to_string(num++) + ".jpg", frame);
		imshow("frame", frame);
		waitKey(1);
	}
	return 0;
}
