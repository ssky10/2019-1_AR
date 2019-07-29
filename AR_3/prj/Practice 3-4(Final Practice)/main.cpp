#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace std;

const string objPath = "../data/3-4/obj.jpg";
const string videoPath = "../data/3-3/greatescape2.mp4";

int main(int argc, char** argv)
{
	Ptr<Feature2D> siftd = xfeatures2d::SIFT::create();
	VideoCapture cam(0), vidio(videoPath);
	Mat Hv2o;

	Mat objImg = imread(objPath), objDesc;
	int width = vidio.get(CAP_PROP_FRAME_WIDTH) - 1;
	int height = vidio.get(CAP_PROP_FRAME_HEIGHT) - 1;

	vector<Point2f> from, to;
	from.push_back(Point2f(0, 0));
	to.push_back(Point2f(0, 0));
	from.push_back(Point2f(width, 0));
	to.push_back(Point2f(objImg.cols - 1, 0));
	from.push_back(Point2f(width, height));
	to.push_back(Point2f(objImg.cols - 1, objImg.rows - 1));
	from.push_back(Point2f(0, height));
	to.push_back(Point2f(0, objImg.rows - 1));
	Hv2o = findHomography(from, to);

	vector<KeyPoint> objkps;
	siftd->detectAndCompute(objImg, Mat(), objkps, objDesc);

	
	Mat camImg, videoImg;
	//on-line
	while (true) {
		double start = (double)getTickCount();
		Mat camDesc;
		cam >> camImg;
		vector<KeyPoint> camkps;
		siftd->detectAndCompute(camImg, Mat(), camkps, camDesc);

		BFMatcher matcher(NORM_L2SQR);
		vector<DMatch> matches, Mo2c, Mc2o;
		matcher.match(objDesc, camDesc, Mo2c);
		matcher.match(camDesc, objDesc, Mc2o);

		for (int i = 0; i < Mc2o.size(); i++)
		{
			if (Mo2c[Mc2o[i].trainIdx].trainIdx == i) {
				matches.push_back(Mc2o[i]);
			}
		}

		if (matches.size() > 100) {

			from.clear(), to.clear();
			for (int i = 0; i < matches.size(); i++) {
				from.push_back(objkps[matches[i].trainIdx].pt);
				to.push_back(camkps[matches[i].queryIdx].pt);
			}

			Mat inliner;
			Mat Ho2c = findHomography(from, to, RANSAC, 3.0, inliner);

			if (countNonZero(inliner) > 100) {
				vidio >> videoImg;
				Mat warpedImg, mask;
				Mat Hv2c = Ho2c * Hv2o;
				warpPerspective(videoImg, warpedImg, Hv2c, camImg.size());
				warpPerspective(Mat(videoImg.size(), CV_8UC1, Scalar(255)), mask, Hv2c, camImg.size());
				warpedImg.copyTo(camImg, mask);
			}
		}
		double end = (double)getTickCount();
		cout << 1/((end - start) / getTickFrequency()) << endl;
		cv::imshow("camImg", camImg);
		cv::waitKey(1);
	}
	return 0;
}
