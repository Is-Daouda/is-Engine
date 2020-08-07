# AndroidStudio
**is::Engine** for [Android Studio](https://developer.android.com/studio).

---

## Prerequisites

- SFML Library (2.4 +)
- Install Android Studio (3.1.3 +)
- Android SDK and NDK (r20b)
- Firebase C++ SDK 4.5.0 (If you need it)

---

## Installation

### Windows
- Download [Android Studio 3.x](https://developer.android.com/studio) (recommended version 3.1.3)
- Download the [Android SDK](https://developer.android.com/studio) and install it in **C:/Android/SDK**
- Download [Android NDK android-ndk-r20b-windows-x86_64](https://developer.android.com/ndk/downloads/older_releases.html) and create a folder on your disk as follows **C:/Android/NDK** then extract the contents of the zip in this folder.
- Set the environment variable **ANDROID_NDK** with the path **C:/Android/NDK**
- Download this [version of SFML](https://github.com/Is-Daouda/SFML-2.5.1-build-for-NDK-r20b) already compiled for Android NDK and extract it in **C:/Android/NDK/sources/sfml**
- Move the **AndroidStudio project** of is::Engine to your **C:/** (C:/AndroidStudio)
- Open the **AndroidStudio** folder with **Android Studio** and start the compilation.

If all goes well you will have a **Hello World Screen** on your **Android emulator**

![Image](./images/demo_screen.png)

**Enjoy!**