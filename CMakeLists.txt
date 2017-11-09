cmake_minimum_required(VERSION 3.5)


project(anpi VERSION 0.0.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

set(COMMON_SOURCES )
set(PLOTSOURCES src/main.cpp)

include_directories("src/core" )
include_directories("src/Process" )
include_directories("src/GUI" )

add_executable(testPlot ${PLOTSOURCES})
target_link_libraries(testPlot PRIVATE python2.7)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
