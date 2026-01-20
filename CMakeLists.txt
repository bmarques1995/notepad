cmake_minimum_required(VERSION 3.28)
project(Notepad LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_helpers/")

include(dep_tracer)
include(target_destination)

add_subdirectory(app)
