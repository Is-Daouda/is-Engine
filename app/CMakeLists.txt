# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

# Uncomment if you want to use Admob
# include_directories(${FIREBASE_INCLUDE_DIR})
# link_directories("${FIREBASE_LIBRARY_DIR}${ANDROID_ABI}/c++/")

set(ISENGINE_ANDROID true) # This confirms that we are using is::Engine to develop on Android
set(ISENGINE_SRC_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp")
set(ISENGINE_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cmake")

include_directories(${SFML_INCLUDE_DIR})
link_directories("${SFML_LIBRARY_DIR}${ANDROID_ABI}/")
link_directories("${SFML_EXT_LIBRARY_DIR}${ANDROID_ABI}/")

message(STATUS "SFML include dir: ${SFML_INCLUDE_DIR}")
message(STATUS "SFML lib dir: ${SFML_LIBRARY_DIR}${ANDROID_ABI}/")
message(STATUS "SFML extlib dir: ${SFML_EXT_LIBRARY_DIR}${ANDROID_ABI}/")
message(STATUS "ABI ${ANDROID_ABI}")

include(${ISENGINE_CMAKE_DIR}/isengine.cmake)
include(${ISENGINE_CMAKE_DIR}/app_src.cmake)

add_library(# Sets the name of the library.
            isengine # You can change this name

            # Sets the library as a shared library.
             SHARED
            # Provides a relative path to your source file(s).
			${isengine}
			${app_src}
            )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                        isengine

                        # Links the target library to the log library
                        # included in the NDK.

                        log
                        android
                        EGL
                        GLESv1_CM

                        sfml-system-d

                        openal

                        # uncomment if you want to use Admob
                        # admob
                        # app

                        sfml-window-d
                        sfml-audio-d
                        sfml-graphics-d
                        sfml-network-d
                        sfml-activity-d
                        -Wl,--whole-archive sfml-main-d -Wl,--no-whole-archive
                        )

