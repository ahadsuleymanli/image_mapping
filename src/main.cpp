#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#include <findlocation.h>

using namespace cv;
using namespace std;


int main(int argc, char** argv )
{

    const char* image_path = "images/StarMap.png";
    if ( argc != 3 )
    {
        printf("usage: ImageClusterer <Image1_Path> <Image2_Path>\n");
        return -1;
    }
    Mat smallImage, largeImage;
    smallImage = imread( argv[1], 1 );
    largeImage = imread( argv[2], 1 );
    // cvtColor(smallImage,smallImage, COLOR_BGR2GRAY);
    // cvtColor(largeImage,largeImage, COLOR_BGR2GRAY);
    if ( !smallImage.data || !largeImage.data )
    {
        printf("Please enter two valid images, small image first, large second. \n");
        return -1;
    }

    int x=0, y=0;

    findLocation(smallImage,largeImage,x,y);
    printf("x,y:%d,%d \n",x,y);

    // namedWindow("Display Image", WINDOW_AUTOSIZE );
    // imshow("Display Image", smallImage);
    // waitKey(0);
    // imshow("Display Image", largeImage);
    // waitKey(0);
    return 0;
}