project(BandedMatrix-Tweaks CXX)

cmake_minimum_required(VERSION 3.4)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(band_tweaks band_tweaks.cpp)
target_link_libraries(band_tweaks blas)

add_executable(tutorial tutorial.cpp)
target_link_libraries(band_tweaks)
