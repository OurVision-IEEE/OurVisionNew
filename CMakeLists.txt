cmake_minimum_required(VERSION 3.16)
project(LearningCMake)

file(GLOB srcs *.cpp *.c)
file(GLOB hdrs *.hpp *.h)

#set(OpenCV_DIR "/usr/local/Cellar/opencv/4.5.1_3/lib/cmake/opencv4/")
set(TESSERACT_DIR "/usr/include/")
set(LEPTONICA_DIR "/usr/include/")
find_package( OpenCV REQUIRED )

include_directories("${CMAKE_CURRENT_LIST_DIR}")
message("${CMAKE_CURRENT_LIST_DIR}")
set(CMAKE_CXX_STANDARD 14)

include_directories( ${OPENCV_DIR} ${OpenCV_INCLUDE_DIRS} ${TESSERACT_DIR} ${LEPTONICA_DIR})
message("${OpenCV_LIBS}")
message("${OPENCV_DIR}")
message("${OpenCV_INCLUDE_DIRS}")
message("${OpenCV_LIBS}")
macro(link_lib name)
    add_executable(LearningCMake ${name}.cpp)
    target_link_libraries(LearningCMake ${OpenCV_LIBS} )
    target_link_libraries(LearningCMake tesseract)
    target_link_libraries(LearningCMake lept)
endmacro()

link_lib(main)
