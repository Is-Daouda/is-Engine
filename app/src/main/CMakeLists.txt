cmake_minimum_required (VERSION 3.11)

add_subdirectory(web/third_party)

project(isengine
  LANGUAGES CXX
  VERSION 1.0.0
)

set(ISENGINE_HTML_5 true) # This confirms that we are using is::Engine to develop on the Web
set(ISENGINE_SRC_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/cpp")
set(ISENGINE_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_compile_definitions(IS_ENGINE_HTML_5)

include(${ISENGINE_CMAKE_DIR}/app_src.cmake)
include(${ISENGINE_CMAKE_DIR}/isengine.cmake)

add_executable(isengine
	${app_src}
	${isengine}
)

target_include_directories(isengine PRIVATE cpp)
target_link_libraries(isengine PRIVATE smk)

set_target_properties(isengine PROPERTIES CXX_STANDARD 17)

# -Wextra -pedantic -Werror
target_compile_options(isengine PRIVATE -Wall)

# Detect emscripten is used.
if(EMSCRIPTEN) 

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
	configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/web/index.html
	${CMAKE_CURRENT_BINARY_DIR}/index.html
	COPYONLY
	)
	configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/env/windows/icon_32.png
	${CMAKE_CURRENT_BINARY_DIR}/favicon.png
	COPYONLY
	)	
	configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/web/loading.png
	${CMAKE_CURRENT_BINARY_DIR}/loading.png
	COPYONLY
	)
	configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/web/sw.js
	${CMAKE_CURRENT_BINARY_DIR}/sw.js
	COPYONLY
	)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/web/images  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/web/scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/web/styles  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	
    # Allow some files to be fetched.
	file(GLOB files "./assets/*" "./assets/*/*")
	foreach(file ${files})
		file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} ${file})
		set_property(TARGET isengine APPEND_STRING PROPERTY LINK_FLAGS  " --preload-file ${file}@/${relative_file}")
	endforeach()
else()
	install(TARGETS isengine RUNTIME DESTINATION "bin")
endif()
