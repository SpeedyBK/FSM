cmake_minimum_required(VERSION 3.14)
project(FSM)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "/home/benjamin/Dependencies/sfml/include")
set(SFML_LIBRARY_DIR "/home/benjamin/Dependencies/sfml/lib")
set(SFML_DIR "/home/benjamin/Dependencies/sfml/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(FSM main.cpp)

target_link_libraries (FSM sfml-graphics sfml-audio sfml-window sfml-system)