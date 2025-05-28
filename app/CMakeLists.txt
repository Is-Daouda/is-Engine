cmake_minimum_required(VERSION 3.4.1)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2/include

        # SDL_internal.h is located in src required by SDL_android_main.c bridge
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2/src

        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_image/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_gfx/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_mixer/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_ttf/include
)

set(ISENGINE_ANDROID true) # This confirms that we are using is::Engine to develop on Android
set(ISENGINE_SRC_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp")
set(ISENGINE_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cmake")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2/ ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_image/ ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_image)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_gfx/ ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_gfx)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_mixer/ ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_mixer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_ttf/ ${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL2_ttf)

#include_directories(${FIREBASE_INCLUDE_DIR})
#link_directories("${FIREBASE_LIBRARY_DIR}${ANDROID_ABI}/c++/")
include(${ISENGINE_CMAKE_DIR}/isengine.cmake)
include(${ISENGINE_CMAKE_DIR}/app_src.cmake)

add_library(
			 isengine

             SHARED
			 
			 # Provides a relative path to your source file(s).
			 ${isengine}
			 ${app_src}
			 )

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_link_libraries( # Specifies the target library.
						isengine
                        SDL2
                        SDL2_image
                        SDL2_gfx
                        SDL2_mixer
                        SDL2_ttf

                        #admob
                        #app

                        ${log-lib} )