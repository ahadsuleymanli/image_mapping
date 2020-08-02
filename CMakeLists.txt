cmake_minimum_required(VERSION 2.8)
project( map_image )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} include )
add_executable( map_image 
    src/main.cpp
    src/templatematch.cpp
    include/templatematch.h
    )
target_link_libraries( map_image ${OpenCV_LIBS} )