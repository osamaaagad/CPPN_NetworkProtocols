cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(NetworkProtocol)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


link_directories(${CMAKE_HOME_DIRECTORY}/include/)

include_directories(
    ${CMAKE_HOME_DIRECTORY}/
    ${CMAKE_HOME_DIRECTORY}/include/
    ${CMAKE_HOME_DIRECTORY}/include/MQTT/
 )

file(GLOB SRC_FILES 
    ${CMAKE_HOME_DIRECTORY}/src/*.cpp
    ${CMAKE_HOME_DIRECTORY}/src/MQTT/*.c
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(
    ${PROJECT_NAME}
    pthread
    rt
)