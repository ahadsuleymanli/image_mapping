#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <chrono>

using namespace std;
using namespace cv;

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60


void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

Mat rotate(Mat src, double angle)      
{
    Mat dst;
    // int top, bottom, left, right;
    // top = (int) (0.05*src.rows); bottom = top;
    // left = (int) (0.05*src.cols); right = left;
    // copyMakeBorder( src, dst, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0) );      
    Point2f pt(src.cols/2., src.rows/2.);         
    Mat r = getRotationMatrix2D(pt, angle, 1.0);      
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;        
}

Point rotate_point(float cx,float cy,float angle,Point p)
{
  float s = sin(angle);
  float c = cos(angle);

  // rotate point
  float xnew = (p.x-cx) * c - (p.y-cy) * s;
  float ynew = (p.x-cx) * s + (p.y-cy) * c;

  return Point(xnew + cx,ynew + cy);
}


int main ( int argc, char** argv )
{
    if ( argc != 3 )
    {
        cout<<"usage: map_image img1 img2"<<endl;
        return 1;
    }
    Mat ref = cv::imread(argv[2]);
    Mat tpl = cv::imread(argv[1]);
    if(ref.empty() || tpl.empty())
    {
        cout << "Error reading file(s)!" << endl;
        return -1;
    }

    Mat gref, gtpl;
    cvtColor(ref, gref, CV_BGR2GRAY);


    const int low_canny = 64;
    Canny(gref, gref, low_canny, low_canny*3);
    double max = 0;
    vector<Point> bestPoints = {};
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int angle = 0 ; angle<365; angle++){
        gtpl = rotate(tpl,angle);
        cvtColor(gtpl, gtpl, CV_BGR2GRAY);
        Canny(gtpl, gtpl, low_canny, low_canny*3);

        Mat res_32f(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
        matchTemplate(gref, gtpl, res_32f, CV_TM_CCOEFF_NORMED);

        Mat res;
        res_32f.convertTo(res, CV_8U, 255.0);

        while(1) 
        {
            double minval, maxval;
            Point minloc, maxloc;
            minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

            if(maxval > 255*0.25)
            {
                // rectangle(ref, maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows), Scalar(0,255,0), 2);
                Point originalPoint1 = rotate_point((maxloc.x + tpl.cols/2),(maxloc.y + tpl.rows/2),angle, maxloc );
                Point originalPoint2 = rotate_point((maxloc.x + tpl.cols/2),(maxloc.y + tpl.rows/2),angle, Point(maxloc.x + tpl.cols, maxloc.y) );
                Point originalPoint3 = rotate_point((maxloc.x + tpl.cols/2),(maxloc.y + tpl.rows/2),angle, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows) );
                Point originalPoint4 = rotate_point((maxloc.x + tpl.cols/2),(maxloc.y + tpl.rows/2),angle, Point(maxloc.x, maxloc.y + tpl.rows) );

                if (maxval>max){
                    max = maxval;
                    bestPoints = {originalPoint1,originalPoint2,originalPoint3,originalPoint4};
                }

                cout<<"found, acc:"<<maxval<<endl;
                
                floodFill(res, maxloc, 0); //mark drawn blob
                
            }
            else
                break;
            
            
        }
        printProgress(angle/365.0);

    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    if (bestPoints.size()){
        polylines(ref, bestPoints, true, Scalar(0,255,0),2,150,0);
        cout << "points:" << "\n";
        cout << bestPoints << "\n";
        imshow("final", ref);
        waitKey(0);
    }
    else
        cout << "no match found" << "\n";


    return 0;
}