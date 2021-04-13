cmake_minimum_required(VERSION 3.15)
project(opencvTest)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "-Wall -Werror")

# if necessary, set OpenCV_DIR variable, like below
# set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../build)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(main
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/point.cpp
  ${PROJECT_SOURCE_DIR}/src/pictures.cpp
  ${PROJECT_SOURCE_DIR}/src/algorithm.cpp
)

add_executable(test
  ${PROJECT_SOURCE_DIR}/src/test.cpp
  ${PROJECT_SOURCE_DIR}/src/point.cpp
)

target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(main ${OpenCV_LIBS})
