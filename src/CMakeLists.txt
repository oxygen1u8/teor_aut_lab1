cmake_minimum_required(VERSION 3.20)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(minimize_dnf)

set(SOURCE_FILES
    ${SRC_DIR}/dnf.cpp
    ${SRC_DIR}/impl.cpp
)

include_directories(
    ${SRC_DIR}
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
    -c -Wall -ggdb")

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
