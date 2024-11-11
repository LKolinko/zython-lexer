cmake_minimum_required(VERSION 3.29)
project(ZLEXER)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES
     "src/*.cpp"
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

add_subdirectory(examples)
