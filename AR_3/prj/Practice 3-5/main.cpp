#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cv;
using namespace std;

const string dataPath = "../data/";
const string imgPath = "../data/imgs/";
const string imgList = "images.txt";

int main(int argc, char** argv)
{
	ifstream in(dataPath + imgList);
	Ptr<Feature2D> siftd = xfeatures2d::SIFT::create();
	int nImgs = 0;

	vector<Mat> objImgs, objDescs;
	vector<vector<KeyPoint>> objkpss;
	vector<string> imgNames;
	for (string sLine; getline(in, sLine); nImgs++) {
		imgNames.push_back(sLine);
		Mat img = imread(imgPath + sLine + ".jpg");
		objImgs.push_back(img);
		Mat desc;
		vector<KeyPoint> objkps;
		siftd->detectAndCompute(img, Mat(), objkps, desc);
		objkpss.push_back(objkps);
		objDescs.push_back(desc);
	}
	
	BFMatcher matcher(NORM_L2SQR);
	matcher.add(objDescs);
	matcher.train();

	VideoCapture cam(0);

	Mat Hv2o;

	/*int width = vidio.get(CAP_PROP_FRAME_WIDTH) - 1;
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
	siftd->detectAndCompute(objImg, Mat(), objkps, objDesc);*/

	
	Mat camImg, videoImg;
	//on-line
	while (true) {
		double start = (double)getTickCount();
		Mat camDesc;
		cam >> camImg;
		vector<KeyPoint> camkps;
		siftd->detectAndCompute(camImg, Mat(), camkps, camDesc);

		vector<vector<DMatch>> M(nImgs);
		vector<DMatch> Mc2o;
		matcher.match(camDesc, Mc2o);

		for (int i = 0; i < Mc2o.size(); i++)
		{
			M[Mc2o[i].imgIdx].push_back(Mc2o[i]);
		}

		for (int o = 0; o < nImgs; o++) {
			if (M[o].size() > 30) {
				vector<Point2f> from, to;
				for (int i = 0; i < M[o].size(); i++) {
					from.push_back(objkpss[o][M[o][i].trainIdx].pt);
					to.push_back(camkps[M[o][i].queryIdx].pt);
				}

				Mat inliner;
				Mat Ho2c = findHomography(from, to, RANSAC, 3.0, inliner);

				if (countNonZero(inliner) > 10) {
					vidio >> videoImg;
					Mat warpedImg, mask;
					Mat Hv2c = Ho2c * Hv2o;
					warpPerspective(videoImg, warpedImg, Hv2c, camImg.size());
					warpPerspective(Mat(videoImg.size(), CV_8UC1, Scalar(255)), mask, Hv2c, camImg.size());
					warpedImg.copyTo(camImg, mask);
				}
			}
		}
		double end = (double)getTickCount();
		cout << 1/((end - start) / getTickFrequency()) << endl;
		cv::imshow("camImg", camImg);
		cv::waitKey(1);
	}
	return 0;
}
