cmake_minimum_required(VERSION 3.10)
project(csv_shaper)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_library(shaper STATIC src/shaper.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC shaper)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(shaper PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()
