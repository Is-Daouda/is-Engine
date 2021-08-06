cmake_minimum_required(VERSION 3.15)
project(isengine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=\"['png']\" -s -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_OGG=1 -s USE_VORBIS=1 -s USE_FREETYPE=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})

set(ISENGINE_HTML_5 true) # This confirms that we are using is::Engine to develop on the Web
set(ISENGINE_SRC_DIR   "cpp")
set(ISENGINE_CMAKE_DIR "cmake")

add_compile_definitions(IS_ENGINE_HTML_5)

include(${ISENGINE_CMAKE_DIR}/app_src.cmake)
include(${ISENGINE_CMAKE_DIR}/isengine.cmake)

add_executable(isengine
	${app_src}
	${isengine}
)

target_link_libraries(isengine ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES} ${FREETYPE_LIBRARIES} -lidbfs.js)

set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " -s DEMANGLE_SUPPORT=1")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " -s DISABLE_EXCEPTION_CATCHING=2")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " -s WASM=1")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " -s TOTAL_MEMORY=134217728")

# Release flags
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " --emrun")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " --js-opts 3")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " --llvm-lto 3")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " --llvm-opts 3")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " -O3")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " -flto")
set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS " --bind")

# Copy the web files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/index.html ${CMAKE_CURRENT_BINARY_DIR}/index.html COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/web/sw.js ${CMAKE_CURRENT_BINARY_DIR}/sw.js COPYONLY)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/web/images  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/web/scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/web/styles  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Allow some files to be fetched.
file(GLOB files "./assets/*" "./assets/*/*")
foreach(file ${files})
	file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} ${file})
	set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS  " --preload-file ${file}@/${relative_file}")
endforeach()