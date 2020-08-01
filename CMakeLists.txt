cmake_minimum_required(VERSION 2.8)
project( ImageClusterer )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} include )
add_executable( ImageClusterer 
    src/main.cpp
    src/findlocation.cpp
    include/findlocation.h
    )
target_link_libraries( ImageClusterer ${OpenCV_LIBS} )