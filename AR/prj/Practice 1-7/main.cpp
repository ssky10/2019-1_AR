#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

const string dataPath = "../data/";

int main(int argc, char** argv)
{
	VideoCapture capture(0);
	QRCodeDetector detector;
	Mat frame, points, qr;
	int num = 1;
	string data;
	//capture.read(frame);
	while (true)
	{
		capture >> frame;
		data = detector.detectAndDecode(frame, points, qr);
		for (int i = 0; i < 4; i++)
		{
			cout << points.at<float>(i, 0) << ',';
			cout << points.at<float>(i, 1) << endl;
		}
		if (!data.empty()) {
			imshow("QR", qr);
			cout << data << endl;
		}
		imshow("frame", frame);
		waitKey(1);
	}
	return 0;
}