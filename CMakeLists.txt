cmake_minimum_required(VERSION 3.0)

project(IMUInitialAlignment)

add_subdirectory(src)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(AlignmentExecutable main.cpp)

target_link_libraries(AlignmentExecutable PRIVATE EulerAnglesCalculator IMUDataReader Plotter)
