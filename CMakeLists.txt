cmake_minimum_required(VERSION 3.10)
project(AltitudeEstimator)
set(CMAKE_CXX_STANDARD 17)

add_executable(altitude_estimator
    src/main.cpp
    src/parser.cpp
    src/outlierRejection.cpp
    src/groundTracker.cpp
    src/heightEstimator.cpp
)

target_include_directories(altitude_estimator PRIVATE src/)