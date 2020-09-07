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

include_directories(${SFML_INCLUDE_DIR})
link_directories("${SFML_LIBRARY_DIR}${ANDROID_ABI}/")
link_directories("${SFML_EXT_LIBRARY_DIR}${ANDROID_ABI}/")

message(STATUS "SFML include dir: ${SFML_INCLUDE_DIR}")
message(STATUS "SFML lib dir: ${SFML_LIBRARY_DIR}${ANDROID_ABI}/")
message(STATUS "SFML extlib dir: ${SFML_EXT_LIBRARY_DIR}${ANDROID_ABI}/")
message(STATUS "ABI ${ANDROID_ABI}")

add_library(# Sets the name of the library.
            isengine # You can change this name

            # Sets the library as a shared library.
             SHARED
            # Provides a relative path to your source file(s).

# --------------------------------- game source --------------------------------------
			src/main/cpp/main.cpp

			# Basic SFML rendering loop
			src/main/cpp/basicSFMLmain.cpp

			# game config
            src/main/cpp/app_src/config/GameConfig.h

			# game system extended
            src/main/cpp/app_src/gamesystem_ext/GameSystemExtended.cpp

			# game scene
			#src/main/cpp/app_src/scenes/...

			# game objects
			#src/main/cpp/app_src/objects/...

			# widgets
			src/main/cpp/app_src/objects/widgets/GameDialog.cpp

# --------------------------------- is::Engine source --------------------------------------
			# core
			src/main/cpp/isEngine/core/GameEngine.cpp

			# system
			src/main/cpp/isEngine/system/display/GameDisplay.cpp
			src/main/cpp/isEngine/system/entity/MainObject.cpp
			src/main/cpp/isEngine/system/function/GameKeyData.cpp
			src/main/cpp/isEngine/system/function/GameSystem.cpp
			src/main/cpp/isEngine/system/function/GameFunction.cpp
			src/main/cpp/isEngine/system/function/GameTime.cpp

            # box 2d source
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/b2BroadPhase.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/b2CollideCircle.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/b2CollideEdge.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/b2CollidePolygon.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/b2Collision.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/b2Distance.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/b2DynamicTree.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/b2TimeOfImpact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2CircleShape.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2EdgeShape.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2ChainShape.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2PolygonShape.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Common/b2BlockAllocator.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Common/b2Draw.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Common/b2Math.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Common/b2Settings.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Common/b2StackAllocator.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Common/b2Timer.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/b2Body.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/b2ContactManager.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/b2Fixture.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/b2Island.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/b2World.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/b2WorldCallbacks.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2CircleContact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2Contact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2GearJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2Joint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2MotorJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2MouseJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2RopeJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2WeldJoint.cpp
			src/main/cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2WheelJoint.cpp

			# tmx lite
			src/main/cpp/isEngine/ext_lib/TMXLite/FreeFuncs.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/ImageLayer.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/LayerGroup.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/Map.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/Object.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/ObjectGroup.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/Property.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/TileLayer.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/Tileset.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/detail/pugixml.cpp
			src/main/cpp/isEngine/ext_lib/TMXLite/miniz.c
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

