# SFML-AndroidStudio-Template

WIP. Android Studio, with the Gradle and CMake build system, template for a Native (and/or Hybrid) App with SFML

## Prerequisites

Brain.exe

Install Android Studio (2.3.3 +)

At the first startup of Android Studio install the SDK and NDK in Android Studio.
I recommend doing it directly in android studio so your sdk and ndk directories are set correctly

Build SFML for android (use libc++_shared, change the build.gradle file in the template for full c++11 support!),
have a look at the SFML wiki there is a tutorial. 

For Building SFML with libc++ android-ndk-r12b is required. Afterwards you can use the latest and greatest from android-studio

**If however, you build SFML from git, you can also build with latest android-ndk**

## How to use

Clone this git, rename the folder and then just open it in android studio (2.3+)

FIX YOUR PATHS AND ABI FILTERS

Now you can simply run the application! 

## Todo

- **CleanUp Paths and abiFilters**
- Support linking of debug libs
