#include <iostream>
#include "opencv2/opencv.hpp"

#define FILE_NUM 50

using namespace cv;
using namespace std;

const string imgPath = "../data/2-2/";

void histogram(Mat inputImg, Mat &outputMat, bool normalize = true) {
	outputMat = Mat(1, 256, CV_32FC1, Scalar(0));
	for (int i = 0; i < inputImg.rows; i++)
		for (int j = 0; j < inputImg.cols; j++)
			outputMat.at<float>(0, inputImg.at<unsigned char>(i, j))++;
	outputMat /= inputImg.total();
}

double calcDistance(Mat hist1, Mat hist2) {
	double result = 0;
	double tmp;
	for (int i = 0; i < hist1.cols; i++) {
		tmp = hist1.at<float>(i) - hist2.at<float>(i);
		result += (tmp*tmp);
	}
	return result;
}

int main(int argc, char** argv)
{
	Mat img = imread(imgPath + "query.jpg", IMREAD_GRAYSCALE);

	Mat queryHist;
	vector<double> inputHist(FILE_NUM);
	vector<int> idx;

	histogram(img, queryHist);

	for (int i = 0; i < FILE_NUM; i++) {
		Mat tmp = imread(imgPath + to_string(i+1) + ".jpg", IMREAD_GRAYSCALE);
		Mat hist;
		histogram(tmp, hist);
		inputHist[i] = calcDistance(queryHist, hist);
	}

	sortIdx(inputHist, idx, SORT_EVERY_ROW);

	for (int i = 0; i < FILE_NUM; i++) {
		cout << "distance between query img and " << (idx[i]+1) << "th img : " << inputHist[idx[i]] << endl;
	}

	return 0;
}
