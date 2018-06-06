#!/bin/sh

PROJECT_ROOT=$PWD
echo $PROJECT_ROOT

if [ ! -d "./build_android" ];then
   mkdir ./build_android
fi

rm -fr ./build_android/*

cd ./build_android

cmake \
-DCMAKE_TOOLCHAIN_FILE="/home/devin/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake" \
-DANDROID_NDK="/home/devin/Android/Sdk/ndk-bundle" \
-DCMAKE_BUILD_TYPE=Release \
-DANDROID_ABI="armeabi-v7a" \
-DANDROID_NATIVE_API_LEVEL=21 \
..

make