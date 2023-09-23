cmake_minimum_required(VERSION 3.5)
project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS})
set(YOUR_DIRECTORY include)
include_directories(${YOUR_DIRECTORY})
set(SOURCES Shape.cpp ShapeDetection.cpp Filters.cpp ${YOUR_DIRECTORY}/Shape.hpp ${YOUR_DIRECTORY}/ShapeDetection.hpp ${YOUR_DIRECTORY}/Filters.hpp)

set(EXECUTABLE OpenCVShapes)


add_executable( ${EXECUTABLE} Main.cpp ${SOURCES} )

target_link_libraries( ${EXECUTABLE} ${OpenCV_LIBS} )

if(MSVC)
  target_compile_options(${EXECUTABLE} PRIVATE /W4 /WX)
else()
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic)
endif()
