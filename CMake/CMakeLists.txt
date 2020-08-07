cmake_minimum_required (VERSION 3.1) 

project(isengine)

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

include(isengine.cmake)
include(app_src.cmake)

# game resources files (image, sound, music, ...)
file(COPY data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(isengine
    ${isengine}
	${app_src}
	resource.rc # application icon
)

target_include_directories(isengine PRIVATE include)
target_link_libraries(isengine sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
