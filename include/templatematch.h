#ifndef TEMPLATEMATCH_H
#define TEMPLATEMATCH_H
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;

vector<Point> templateMatch(Mat& tpl, Mat& ref);
void printProgress(double percentage);
Mat rotate(Mat src, double angle);
Point rotate_point(float cx,float cy,float angle,Point p);


#endif