#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include "templatematch.h"

using namespace std;
using namespace cv;

int main ( int argc, char** argv )
{
    if ( argc != 3 )
    {
        cout<<"usage: map_image smallimage largeimage"<<endl;
        return 1;
    }

    Mat tpl = cv::imread(argv[1]);
    Mat ref = cv::imread(argv[2]);
    if(ref.empty() || tpl.empty())
    {
        cout << "Error reading file(s)!" << endl;
        return -1;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    // match and get matching rectangle as a Points vector
    vector<Point> bestPoints = templateMatch(tpl, ref);
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    // print results
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