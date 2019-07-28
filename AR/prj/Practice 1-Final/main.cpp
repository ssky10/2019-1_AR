#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

const string dataPath = "../data/";

int main(int argc, char** argv)
{
	VideoCapture capture(1);
	VideoCapture capture2;
	QRCodeDetector detector;
	Mat frame, points, qr, frame2, homoM;
	string data;
	vector<Point2f> from(4), to(4);
	while (true)
	{
		capture >> frame;
		data = detector.detectAndDecode(frame, points, qr);
		if (!data.empty()) {
			if (!capture2.isOpened()) {
				capture2.open(dataPath + data);
				int width = capture2.get(CAP_PROP_FRAME_WIDTH) - 1;
				int height = capture2.get(CAP_PROP_FRAME_HEIGHT) - 1;
				from[0] = Point2f(0, 0);
				from[1] = Point2f(width, 0);
				from[2] = Point2f(width, height);
				from[3] = Point2f(0, height);
			}
			capture2 >> frame2;

			for (int i = 0; i < 4; i++)
				to[i] = Point2f(points.at<float>(i, 0), points.at<float>(i, 1));

			homoM = findHomography(from, to);
			Mat mask;
			warpPerspective(Mat(frame2.size(), CV_8UC1, Scalar(255)), mask, homoM, frame.size());
			warpPerspective(frame2, frame2, homoM, frame.size());
			
			frame2.copyTo(frame, mask);
		}
		imshow("frame", frame);
		waitKey(1);
	}
	return 0;
}
