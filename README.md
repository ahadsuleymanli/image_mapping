# image_mapping

Given two images one large, one smaller that is cropped from the large image, 
returns the coordinates of the location it was cropped out of.

#### Usage
```./map_image <small_img> <large_img>```

#### Requirements:
- linux
- opencv
- c++11 compatible gcc

#### Build
```./compile_and_run.sh```

#### Implementation
Matches are done through rotating the template image by 1 degree increments and using cv::matchTemplate function to find a match. 
The original coordinates are calculated after a match is made.
