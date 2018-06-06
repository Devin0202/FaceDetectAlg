cmake_minimum_required(VERSION 3.9)
project(FaceDetect)
set(PROJECT_DIR ${PROJECT_SOURCE_DIR})

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(LIBRARY_OUTPUT_PATH ${PROJECT_DIR}/lib/)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_DIR}/bin/)
    # This is for CLion
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fPIC")
    add_definitions(-DBUILD_FOR_LINUX)
    find_package(OpenCV REQUIRED)

    include_directories(${PROJECT_DIR}/facedetector_haar)
    add_library(FaceDetect SHARED library.cpp ${PROJECT_DIR}/facedetector_haar/facedetector_haar.cpp)

    target_link_libraries(FaceDetect opencv_objdetect)
    target_link_libraries(FaceDetect opencv_imgproc)
    target_link_libraries(FaceDetect opencv_highgui)
    target_link_libraries(FaceDetect opencv_core)

    link_directories(${PROJECT_DIR}/lib)
    add_executable(demo main.cpp)
    target_link_libraries(demo FaceDetect)
ENDIF()

IF (CMAKE_SYSTEM_NAME MATCHES "Android")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fPIC")
    add_definitions(-DBUILD_FOR_ANDROID)

    # OpenCV
#    set(OpenCV_DIR /home/devin/software/8009_android_toolchain/opencv2.4.9_build_android_tbb)
#    set(OpenCV_INCLUDE_DIRS /home/devin/software/8009_android_toolchain/opencv2.4.9_build_android_tbb/install/sdk/native/jni/include)
#    set(TBB_INCLUDE_DIRS /home/devin/software/8009_android_toolchain/opencv2.4.9_build_android_tbb/3rdparty/tbb/tbb41_20130116oss/include/)
#    include_directories(${OpenCV_INCLUDE_DIRS})
#    include_directories(${TBB_INCLUDE_DIRS})
#    link_directories(${OpenCV_DIR}/install/sdk/native/libs/armeabi-v7a)

    include_directories(${PROJECT_DIR}/facedetector_haar)
    include_directories(/home/devin/MyHiGit/FaceDetect/libopencv4android)
    link_directories(/home/devin/MyHiGit/FaceDetect/libopencv4android)
    add_library(FaceDetect SHARED library.cpp ${PROJECT_DIR}/facedetector_haar/facedetector_haar.cpp)

#    target_link_libraries(FaceDetect libtiff)

#    target_link_libraries(FaceDetect libtbb)
#    target_link_libraries(FaceDetect IlmImf)
#    target_link_libraries(FaceDetect libjasper)

    target_link_libraries(FaceDetect opencv_objdetect)
    target_link_libraries(FaceDetect opencv_imgproc)
    target_link_libraries(FaceDetect opencv_highgui)
    target_link_libraries(FaceDetect opencv_core)

    target_link_libraries(FaceDetect log)
    target_link_libraries(FaceDetect z)
    target_link_libraries(FaceDetect libpng)
    target_link_libraries(FaceDetect libjpeg)
    set(NEON_ENABLE on)
ENDIF()