#ifndef FINDLOCATION_H
#define FINDLOCATION_H
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;

void findLocation(Mat& small, Mat& large, int& x, int& y );

#endif