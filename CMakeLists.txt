cmake_minimum_required(VERSION 3.29)
project(zythonlexser)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES zythonlexser
     "*.h"
     "*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES}) 