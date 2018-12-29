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

# uncomment if you want to use Admob
# include_directories(${FIREBASE_INCLUDE_DIR})
# link_directories("${FIREBASE_LIBRARY_DIR}${ANDROID_ABI}/c++/")

include_directories(${SFML_INCLUDE_DIR})
link_directories("${SFML_LIBRARY_DIR}${ANDROID_ABI}/")
link_directories("${SFML_EXT_LIBRARY_DIR}${ANDROID_ABI}/")

message(STATUS "SFML include dir: ${SFML_INCLUDE_DIR}")
message(STATUS "SFML lib dir: ${SFML_LIBRARY_DIR}${ANDROID_ABI}/")
message(STATUS "SFML extlib dir: ${SFML_EXT_LIBRARY_DIR}${ANDROID_ABI}/")
message(STATUS "ABI ${ANDROID_ABI}")

add_library(# Sets the name of the library.
            gamelib # your can change this name

            # Sets the library as a shared library.
             SHARED
            # Provides a relative path to your source file(s).
			src/main/cpp/app_modules/main.cpp

			# system
			src/main/cpp/app_modules/system/display/GameDisplay.cpp
			src/main/cpp/app_modules/system/entity/MainObject.cpp
			src/main/cpp/app_modules/system/function/GameSystem.cpp
			src/main/cpp/app_modules/system/function/GameFunction.cpp
			src/main/cpp/app_modules/system/function/GameTime.cpp

			# core
			src/main/cpp/app_modules/core/GameEngine.cpp
			src/main/cpp/app_modules/core/GameSystemExtended.cpp

			# game scene
			src/main/cpp/app_modules/scene/GameEndScreen.cpp
			src/main/cpp/app_modules/scene/GameIntro.cpp
			src/main/cpp/app_modules/scene/GameLevelConstructor.cpp
			src/main/cpp/app_modules/scene/GameLevelDraw.cpp
			src/main/cpp/app_modules/scene/GameLevelLoadResource.cpp
			src/main/cpp/app_modules/scene/GameLevelStep.cpp
			src/main/cpp/app_modules/scene/GameLevelStepSubFunction.cpp
			src/main/cpp/app_modules/scene/GameMenu.cpp
			src/main/cpp/app_modules/scene/GameMenuDraw.cpp
			src/main/cpp/app_modules/scene/GameMenuLoadResource.cpp
			src/main/cpp/app_modules/scene/GameOver.cpp
			#src/main/cpp/app_modules/scene/...

			# gameplay object
			src/main/cpp/app_modules/gameobj/Bloc.cpp
			src/main/cpp/app_modules/gameobj/Bonus.cpp
			src/main/cpp/app_modules/gameobj/Goal.cpp
			src/main/cpp/app_modules/gameobj/HUD.cpp
			src/main/cpp/app_modules/gameobj/LevelTile.cpp
			src/main/cpp/app_modules/gameobj/PauseButton.cpp
			src/main/cpp/app_modules/gameobj/Player.cpp
			#src/main/cpp/app_modules/gameobj/...
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
                        gamelib

                        # Links the target library to the log library
                        # included in the NDK.

                        log
                        android
                        EGL
                        GLESv1_CM

                        sfml-system

                        openal

                        # uncomment if you want to use Admob
                        # admob
                        # app

                        sfml-window
                        sfml-audio
                        sfml-graphics
                        sfml-network
                        sfml-activity
                        -Wl,--whole-archive sfml-main -Wl,--no-whole-archive
                        )

