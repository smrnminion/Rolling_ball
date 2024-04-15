cmake_minimum_required(VERSION 3.10)

project(Rolling_ball)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(RollingBallLib rolling_ball.cpp)
target_link_libraries(RollingBallLib ${OpenCV_LIBS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(RollingBallTest main.cpp)
target_link_libraries(RollingBallTest RollingBallLib)

install(TARGETS RollingBallTest DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)