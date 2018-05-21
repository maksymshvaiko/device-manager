cmake_minimum_required(VERSION 3.0)
project (device-manager)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME}  mosquittopp)
