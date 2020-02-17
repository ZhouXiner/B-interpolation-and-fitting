cmake_minimum_required(VERSION 3.10)
project(B_Spline_surface)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE  "-std=c++17 -O3 -fopenmp -pthread")


include_directories("/usr/include/eigen3")

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

set(THIRD_PARTY_LIBS
        ${OpenCV_LIBS}
        ${GLUT_LIBRARY}
        ${OPENGL_LIBRARY}
        )
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)

add_executable(B_Spline_surface main.cpp)
target_link_libraries(B_Spline_surface  B_Spline ${THIRD_PARTY_LIBS} stdc++fs)