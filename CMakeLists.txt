cmake_minimum_required(VERSION 3.20)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${ROOT_DIR}/src)
set(LIB_DIR ${SRC_DIR}/build)

project(lab1)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
)

include_directories(
    ${SRC_DIR}
)

target_link_directories(${PROJECT_NAME} PUBLIC ${LIB_DIR})
target_link_libraries(${PROJECT_NAME} minimize_dnf)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -c -Wall -ggdb")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp ${PROJECT_NAME} ${ROOT_DIR}/${PROJECT_NAME}
    COMMENT "[post] Create disassemble file ${PROJECT_NAME}.dis"
)

