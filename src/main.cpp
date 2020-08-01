#include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>

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

    findLocation(smallImage,largeImage,x,y);
    printf("x,y:%d,%d \n",x,y);

    if (x!=-1 && y!=-1){
        imshow("Display Image", largeImage);
        waitKey(0);
    }
    return 0;
}