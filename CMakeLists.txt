cmake_minimum_required(VERSION 2.8.9)
project (device-manager)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
