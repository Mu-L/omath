cmake_minimum_required(VERSION 3.28.1)

project(cv-sdk)

add_library(cv-sdk INTERFACE)
target_include_directories(cv-sdk INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)


if (WIN32)
    target_link_directories(cv-sdk INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>)
endif()
