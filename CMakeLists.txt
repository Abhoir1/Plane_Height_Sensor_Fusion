cmake_minimum_required(VERSION 3.10)
project(AltitudeEstimator)
set(CMAKE_CXX_STANDARD 17)

add_executable(altitude_estimator
    src/main.cpp
    src/csvParser.cpp
    src/outlierRejection.cpp
    src/groundTracker.cpp
    src/heightEstimator.cpp
)

target_include_directories(altitude_estimator PRIVATE src/)
# Copy data folder into build directory so relative paths work
file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/data)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)