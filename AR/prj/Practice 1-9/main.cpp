#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

const string dataPath = "../data/";

int main(int argc, char** argv)
{
	VideoCapture capture(0);
	VideoCapture capture2;
	QRCodeDetector detector;
	Mat frame, points, qr, frame2;
	int num = 1;
	string data;
	//capture.read(frame);
	while (true)
	{
		capture >> frame;
		data = detector.detectAndDecode(frame, points, qr);
		if (!data.empty()) {
			if (!capture2.isOpened()) capture2.open(dataPath + data);
			capture2 >> frame2;
			putText(frame, data, Point(points.at<float>(0, 0), points.at<float>(0, 1)), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0));
			for (int i = 0; i < 4; i++)
			{
				line(frame,
					Point(points.at<float>(i, 0), points.at<float>(i, 1)),
					Point(points.at<float>((i + 1) % 4, 0), points.at<float>((i + 1) % 4, 1)),
					Scalar(i == 0 ? 255 : 0, i == 1 ? 255 : 0, i == 2 ? 255 : 0),
					4);
			}
			imshow("QR", qr);
			cout << data << endl;
			imshow(data, frame2);
		}
		imshow("frame", frame);
		waitKey(1);
	}
	return 0;
}
