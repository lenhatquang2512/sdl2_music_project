#Sample CMakeLists to build SDL project written by Quang N Le
cmake_minimum_required(VERSION 3.0.0)
project(sdl_demo VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14) # Default to C++14
  endif()

set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_CXX_FLAGS "-std=c++14") 
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -Wall -Wextra -Wpedantic -g")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

include_directories(
    include
    ${SDL2_INCLUDE_DIRS})

set(SDL_PROJECT_SOURCES src/main.cpp)
set(EXECUTABLE sdl_demo)
add_executable(${EXECUTABLE} ${SDL_PROJECT_SOURCES})
target_link_libraries(${EXECUTABLE} PUBLIC ${SDL2_LIBRARIES})

enable_testing()
add_test(NAME ${EXECUTABLE} COMMAND ${EXECUTABLE})
