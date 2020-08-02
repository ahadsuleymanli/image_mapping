#include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>
#include <chrono>

#include <findlocation.h>

using namespace cv;
using namespace std;


int main(int argc, char** argv )
{
    Mat smallImage, largeImage;
    int x=-1, y=-1;


    if ( argc != 3 )
    {
        printf("usage: ImageClusterer <Image1_Path> <Image2_Path>\n");
        return -1;
    }
    
    smallImage = imread( argv[1], 1 );
    largeImage = imread( argv[2], 1 );

    if ( !smallImage.data || !largeImage.data )
    {
        printf("Please enter two valid images, small image first, large second. \n");
        return -1;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    findLocation(smallImage,largeImage,x,y);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    printf("x,y:%d,%d \n",x,y);
    int h = smallImage.rows;
    int w = smallImage.cols;

    printf("four points:%d,%d %d,%d %d,%d %d,%d \n",x,y,x+w,y,x+w,y+h,x,y+h);
    if (x!=-1 && y!=-1 || true){
        namedWindow("Display", WINDOW_AUTOSIZE );
        Size size(960,540);
        resize(largeImage,largeImage, size) ;
        imshow("Display", largeImage);
        waitKey(0);
    }
    return 0;
}