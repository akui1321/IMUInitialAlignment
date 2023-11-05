add_library(EulerAnglesCalculator EulerAnglesCalculator.cpp)
add_library(IMUDataReader IMUDataReader.cpp)
add_library(Plotter Plotter.cpp)

target_include_directories(EulerAnglesCalculator PUBLIC ../include)
target_include_directories(IMUDataReader PUBLIC ../include)
target_include_directories(Plotter PUBLIC ../include)
