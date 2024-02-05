#Sample CMakeLists to build SDL project written by Quang N Le
cmake_minimum_required(VERSION 3.0.0)
project(sdl_demo VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11) # Default to C++14
endif()

set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_CXX_FLAGS "-std=c++14") 
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -Wall -Wextra -Wpedantic -g")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Needed so that cmake uses our find modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")

include_directories(
    include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
)

set(lib_names SDL2_First_Graphics)
add_library(SDL2_First_Graphics SHARED lib/mainClassSampleLib.cpp) #do not need header files in include

set(SDL_PROJECT_SOURCES     
                        # src/main.cpp
                        # src/bitmap_sample.cpp
                        # src/health_bar_animation.cpp
                        # src/mainClassSample.cpp
                        # src/image_fetch_sample.cpp
                        src/testSoundBasics.cpp
)
set(EXECUTABLE sdl_demo)
add_executable(${EXECUTABLE} ${SDL_PROJECT_SOURCES})
target_link_libraries(${EXECUTABLE} PUBLIC 
                                            # ${SDL2_LIBRARIES} 
                                            SDL2::Main SDL2::Image GL
                                            SDL2::Net SDL2::Mixer SDL2::Image SDL2::TTF SDL2::GFX 
                                            ${lib_names} 
                                            # ${SDL2_IMAGE_LIBRARIES}
                                            # ${SDL2_TTF_LIBRARIES}
)
target_include_directories(${EXECUTABLE} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Individual linking for each separate file
# add_executable(image_fetch_sample src/image_fetch_sample.cpp)
# target_link_libraries(image_fetch_sample PUBLIC SDL2::Main SDL2::Image GL)
add_executable(health_bar_animation src/health_bar_animation.cpp)
target_link_libraries(health_bar_animation PUBLIC SDL2::Main SDL2::Image GL)
add_executable(mainClassSample src/mainClassSample.cpp)
target_link_libraries(mainClassSample PUBLIC SDL2::Main SDL2::Image GL ${lib_names})
target_include_directories(mainClassSample PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()
add_test(NAME ${EXECUTABLE} COMMAND ${EXECUTABLE})