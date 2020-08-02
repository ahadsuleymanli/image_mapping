#include <iostream>
#include <findlocation.h>

using namespace cv;


void findLocation(Mat& small, Mat& large, int& x, int& y ){

    int windows_n_rows;
    int windows_n_cols;
    int step = 1;
    bool isEqual = false;
    
    windows_n_rows = small.rows;
    windows_n_cols = small.cols;
    Mat roi;
    Scalar roiIntensity;
    Scalar intensity;

    Mat small2;
    Mat small3;
    Mat small4;

    cv::rotate(small, small2, 0);
    cv::rotate(small, small3, 1);
    cv::rotate(small, small4, 2);
    Mat* mats[4] = {&small,&small2,&small3,&small4};
    intensity = mean(small);
    std::cout<<"image size:"<<large.rows<<" "<<large.cols<<"\n";
    std::cout<<"window size:"<<windows_n_rows<<" "<<windows_n_cols<<"\n";


    for (int row = 0; row <= large.rows - windows_n_rows; row += step)
    {
        // Cycle col step
        for (int col = 0; col <= large.cols - windows_n_cols; col += step)
        {
            // ROI window:
            Rect window(col, row, windows_n_rows, windows_n_cols);

            roi = large(window);
            roiIntensity = mean(roi);

            if ( roiIntensity == intensity  ){
                for (int i = 0 ; i<4 ; i++){

    
                    isEqual = sum(*mats[i] != roi) == Scalar(0,0,0,0);
                    if (isEqual){
                        rectangle(large, window, Scalar(255), 1, 8, 0);
                        x = col;
                        y = row;
                        break;
                    }
                    if (isEqual) break;
                }  
            }
        }
        if (isEqual) break;
    }


}
