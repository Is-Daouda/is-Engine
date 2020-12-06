cmake_minimum_required (VERSION 3.1) 

project(isengine)

set(ISENGINE_PC true) # This confirms that we are using is::Engine to develop on PC (Windows / Linux)
set(ISENGINE_MAIN_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main")
set(ISENGINE_SRC_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/cpp")
set(ISENGINE_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app/src/main/cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# SFML on Windows OS
if (WIN32)
	set (SFML_DIR "C:/SFML/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
	
	# OpenAL lib
	file(COPY "C:/SFML/bin/openal32.dll" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})	
endif()

# Find SFML
find_package(SFML REQUIRED  COMPONENTS system window graphics network audio)

include(${ISENGINE_CMAKE_DIR}/isengine.cmake)
include(${ISENGINE_CMAKE_DIR}/app_src.cmake)

# game resources files (image, sound, music, ...)
file(COPY ${ISENGINE_MAIN_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(isengine
    ${isengine}
	${app_src}
	${ISENGINE_CMAKE_DIR}/resource.rc # application icon
)

target_include_directories(isengine PRIVATE include)
target_link_libraries(isengine sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
