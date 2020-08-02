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
A window with the size of the template image is being slid across the original image, if pixel intensities match, 
the template image is being rotated 4 times with 90 degree increments and exact equality is checked.