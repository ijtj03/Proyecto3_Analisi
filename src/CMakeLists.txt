cmake_minimum_required(VERSION 3.5)


project(anpi VERSION 0.0.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

set(COMMON_SOURCES )
set(PLOTSOURCES main.cpp)

include_directories("./core" )

add_executable(testPlot ${PLOTSOURCES})
target_link_libraries(testPlot PRIVATE python2.7)
