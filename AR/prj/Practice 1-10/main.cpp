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
	Mat frame, points, qr, frame2, homoM;
	Mat roi;
	int num = 1;
	string data;
	vector<Point2f> from(4), to(4);
	//capture.read(frame);
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
			{
				line(frame,
					Point(points.at<float>(i, 0), points.at<float>(i, 1)),
					Point(points.at<float>((i + 1) % 4, 0), points.at<float>((i + 1) % 4, 1)),
					Scalar(i == 0 ? 255 : 0, i == 1 ? 255 : 0, i == 2 ? 255 : 0),
					4);
				to[i] = Point2f(points.at<float>(i, 0), points.at<float>(i, 1));
			}
			homoM = findHomography(from, to);
			warpPerspective(frame2, frame2, homoM, frame.size());
			imshow(data, frame2);
		}
		imshow("frame", frame);
		waitKey(10);
	}
	return 0;
}
