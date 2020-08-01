#include <iostream>
#include <findlocation.h>

using namespace cv;


 bool matIsEqual(const cv::Mat mat1, const cv::Mat mat2){
    // treat two empty mat as identical as well
    if (mat1.empty() && mat2.empty()) {
        return true;
    }
    // if dimensionality of two mat is not identical, these two mat is not identical
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows || mat1.dims != mat2.dims) {
        return false;
    }
    cv::Mat diff;
    cv::compare(mat1, mat2, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    return nz==0;
}

void findLocation(Mat& small, Mat& large, int& x, int& y ){

    int windows_n_rows;
    int windows_n_cols;
    int step = 1;
    bool isEqual = false;

    windows_n_rows = small.rows;
    windows_n_cols = small.cols;

    std::cout<<"image size:"<<large.rows<<" "<<large.cols<<"\n";
    std::cout<<"window size:"<<windows_n_rows<<" "<<windows_n_cols<<"\n";

    for (int row = 0; row <= large.rows - windows_n_rows; row += step)
    {
        // Cycle col step
        for (int col = 0; col <= large.cols - windows_n_cols; col += step)
        {
            // ROI window:
            Rect window(col, row, windows_n_rows, windows_n_cols);

            Mat Roi = large(window);
            isEqual = (sum(small != Roi) == Scalar(0,0,0,0));

            if (isEqual){
                rectangle(large, window, Scalar(255), 1, 8, 0);
                x = col;
                y = row;
                break;
            }

        }
        if (isEqual)
            break;
    }

}
