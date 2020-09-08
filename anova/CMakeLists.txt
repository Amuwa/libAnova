# @brief A CMakeLists.txt file for libanova. 
# @author Bernard Longho(@blongho)
# @since 2020-08-18

cmake_minimum_required (VERSION 3.0)

project(anovacpp)

set(EXECUTABLE anovacpp)

include_directories(headers)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable (${EXECUTABLE} ${SOURCE_FILES} "main.cpp")
