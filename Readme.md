![header](./images/is_Engine_logo.png)
----------------------------

# is::Engine (Infinity Solutions::Engine) 3.0

**is::Engine** is a 2D open source game engine based on **SFML** which allows you to easily develop video games on **Android and PC (Windows, Linux)**.

[![SFML logo](https://www.sfml-dev.org/images/logo.png)](https://www.sfml-dev.org) [![logo](https://i.imgur.com/tri24Y5.png)](https://github.com/TheMaverickProgrammer/Swoosh) [![Box2D Logo](https://box2d.org/images/logo.svg)](https://github.com/erincatto/box2d) [![Tiled Logo](https://i.servimg.com/u/f48/20/16/75/27/tiled_10.png)](https://www.mapeditor.org) [![Admob Logo](https://i48.servimg.com/u/f48/20/16/75/27/admob_10.png)](https://admob.google.com/) [![Tiny File Dialog](https://a.fsdn.com/allura/p/tinyfiledialogs/icon?1582196333?&w=90)](https://github.com/native-toolkit/tinyfiledialogs)

## Features
- Language manager (English and French language support by default)
- Scene System
- Automatic management of a window
- SDM (Step and Draw Manager)
- GSM (Game Sound Manager)
- [TMX Lite](https://github.com/Is-Daouda/is-Engine-TMXLite)
- [TMX Loader](https://github.com/Is-Daouda/is-Engine-TMXLoader)
- Entity system
- Object Event System
- Button System
- Background System
- Sprite Animation
- Basic collision engine
- 2D physic engine (Box 2D)
- Screen Transition effect (SWOOSH Library)
- Message Box System (Modifiable appearance via Sprites and Font)
- Dialog Box System (as for RPG games)
- [Windows, Linux] Tiny File Dialogs to manage the dialog boxes of type: Message, File Save, Load File, Folder Selection
- Game Configuration System (sound, music, language, keyboard key, file path, ...)
- Game Save System
- [Android] Virtual Game Pad with 6 keys (multi directional cross and A - B button)
- [Android] Virtual Game Pad Configuration (Adjust Position, transparency, ...)
- [Android] Show Ad Banner
- [Android] Show Reward Video

## What's new in version 3.0 ?
- Support for **TMXLite** and **TMXLoader** library: which allows you to use the [Tiled editor](https://www.mapeditor.org) with the engine.
Official supported version is **[TMXLite](https://github.com/Is-Daouda/is-Engine-TMXLite)** but you can use another engine version with **[TMXLoader](https://github.com/Is-Daouda/is-Engine-TMXLoader)**
- Use Android Studio, CMake, Visual Studio and Code::Blocks with the same project
- **Button System:** Allows you to create customizable buttons and use them in your games
- **Event system for object:** allows to use SFML events in objects
- **Engine optimization:** The games are two (2) times faster
- **Android Studio 4.0.1** support

## Extras
The engine comes with a **[Demo (2D Platform Game)](https://github.com/Is-Daouda/is-Engine-Demo)** that uses only the functions of the engine, in order to show you its power and how to use it. Now imagine what you can do when you use Box 2D and the other tools!

[![Image](https://i48.servimg.com/u/f48/20/16/75/27/is_eng20.png)](https://github.com/Is-Daouda/is-Engine-Demo)

## Game Engine User Guide
- [English version](./doc/isEngine_api_doc_eng.html)
- [French version](./doc/isEngine_api_doc_fr.html)

## Example of a project created with the engine
- [I Can Transform](https://play.google.com/store/apps/details?id=com.isdaouda.icantransform&hl=En)
- [Pac-Pac Prandial War](https://www.youtube.com/watch?v=7CXkiD_jTRg&t=25s&authuser=0)
- [Soldier VS Zombies](https://www.youtube.com/watch?v=qK-Aj-7-czM&authuser=0)

## Prerequisites
- [SFML Library (2.4 +)](https://www.sfml-dev.org/download.php)
- GCC Compiler (7.3 +)

---

## How to use is::Engine with the different development tools:
## Android Studio
**1. Prerequisites**
- Android Studio (4.0.1 +)
- Android SDK and NDK (r20b)
- Firebase C++ SDK 4.5.0 (If you need it)

**2. Installation**
##### Windows
1. Download [Android Studio 3.x](https://developer.android.com/studio) (recommended version 4.0.1).
2. Download the [Android SDK](https://developer.android.com/studio) and install it in **C:/Android/SDK**.
3. Download [Android NDK android-ndk-r20b-windows-x86_64](https://developer.android.com/ndk/downloads/older_releases.html) and create a folder on your disk as follows **C:/Android/NDK** then extract the contents of the zip in this folder.
4. Set the environment variable **ANDROID_NDK** with the path **C:/Android/NDK**.
5. Download this [version of SFML](https://github.com/Is-Daouda/SFML-2.5.1-build-for-NDK-r20b) already compiled for Android NDK and extract it in **C:/Android/NDK/sources/sfml**.
6. Move the **is-Engine** project to your **C:/ (C:/is-Engine)**.
7. Open the **is-Engine** folder with **Android Studio** and start the compilation.

If all goes well you will have a **Hello World Screen** on your **Android emulator**.

![Image](https://github.com/Is-Daouda/is-Engine/blob/2.2.x/images/demo_screen.png)

**Enjoy!**

**3. Adding Source Files**
- So that Android Studio can detect your source files (.cpp) and compile them you must include them in the **CMakeLists.txt** file which is in **is-Engine/app**.

**4. Application location**
- The application can be found in **is-Engine/app/build/outputs/apk**.

---

## CMake
**1. Prerequisites**
- CMake (3.1 +)

**2. Installation**
#### Windows
1. Compile SFML with CMake to have **static libraries** and put on **C:/ (C:/SFML)**.
2. Move the **is-Engine** project to your **C:/ (C:/is-Engine)**.
3. Execute this command :
```bash
cmake -S "C:/is-Engine" -B "C:/build"
cd build
make
```

#### Linux
1. Install SFML 2.5.1 on your machine.
2. Move the **is-Engine** project to **/home/user/ (/home/user/is-Engine)**.
3. Execute this command :
```bash
sudo cmake -S "is-Engine" -B "build"
cd build
sudo make
```

**3. After installation**
- You will have a **bin** folder in which the engine demo is located.

**5. Adding Source Files**
- In order for CMake to detect your source files (.cpp) you must include them in the **app_src.cmake** file which is located in the **is-Engine/app/src/main/cmake** location.

---

## Visual Studio Code
This project uses the template of **andrew-r-king**. For more information on this template [click here](https://github.com/andrew-r-king/sfml-vscode-boilerplate).

**1. Prerequisites**
#### Windows
- [SFML 2.5.1 - GCC 7.3.0 MinGW (DW2) 32-bit](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip)
- [GCC 7.3.0 MinGW (DW2) 32-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download)
- [Git Bash](https://git-scm.com/downloads)

#### Linux
- Get SFML 2.5.1 from your distro if it has it, or compile from source.

**2. Installation**
#### Windows
1. Download & Extract SFML 2.5.1 to **C:/SFML/** where the bin/lib/include folders are contained within.
2. Download & Extract MinGW to **C:/mingw32/** where the bin/lib/include folders are contained within.

#### Linux
1. Ensure the GCC Toolchain is installed (**sudo apt install build-essential**).
2. Run **sudo apt install libsfml-dev**. The SFML version you got will vary depending on the distro. 2.5.1 is included in [Ubuntu 19.04 Disco Dingo](http://cdimage.ubuntu.com/daily-live/current/HEADER.html) for example.

**3. Opening the project with the IDE:**
#### Windows
1. Run the file **open_vscode.bat** in the main directory.

#### Linux
2. Execute this command in the main directory:
```bash
code -n "./app/src/main"
```

#### All
3. Or open the **is-Engine/app/src/main** folder with **Solution Explorer**.

**4. Executable location**
- The compiler files can be found in **is-Engine/app/src/main/bin-vscode**.

---

## Code::Blocks
**1. Prerequisites**

#### Windows
- [Code::Blocks 20.03 MinGW](https://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/codeblocks-20.03mingw-setup.exe/download)

#### Linux
- Code::Blocks 20.03

**2. Installation**
#### Windows
1. Compile SFML and put on **C:/ (C:/SFML_MinGW)**. The folder must have an **include** subfolder and a **lib** subfolder which contains the **static** (.a) and **Dynamic Link Library** (.dll) files.

#### Linux
1. Ensure the GCC Toolchain is installed (**sudo apt install build-essential**).
2. Run **sudo apt install libsfml-dev**. The SFML version you got will vary depending on the distro. 2.5.1 is included in [Ubuntu 19.04 Disco Dingo](http://cdimage.ubuntu.com/daily-live/current/HEADER.html) for example.

**3. Opening the project with the IDE:**

#### Windows
1. Run the file **open_codeblocks.bat** in the main directory.
2. Or open the file **is-Engine-windows.cbp** in the location **is-Engine/app/src/main**

#### Linux
1. Execute this command in the main directory:
```bash
codeblocks "./app/src/main/is-Engine-linux.cbp"
```
2. Or open the file **is-Engine-linux.cbp** in the location **is-Engine/app/src/main**.

**3. Executable location**
- The compiler files can be found in **is-Engine/app/src/main/bin-codeblocks**.

---

## Change application icon:
#### Android
- To change the icon of the application you must go to the location **is-Engine/app/src/main/res** replace all the images (PNG) which are in the **drawable** subfolders.

#### Windows
- To change the icon of the application you must go to the location **is-Engine/app/src/main/env/windows** replace all the images **(Attention CMake uses the same resources).**

#### Linux
- To change the icon of the application you must go to the location **is-Engine/app/src/main/env/linux**.

---

## Description of the project structure:
![header](./images/is_Engine_structure.png)
----------------------------
- The source files of the project can be found in the **is-Engine/app/src/main/cpp** location.

#### `main.cpp` file
Contains the entry point of the program, inside there are two instructions :
- `game.play()`: Launches the engine rendering loop which allows to manage the introduction screen, main menu, level and game over.
- `game.basicSFMLmain()` (disabled by default): Launches the display of a classic SFML window. The implementation is in the `basicSFMLmain.cpp` file. *Very useful if you already have a project under development and you want to associate it with the engine. You can also use it to implement your own components to the engine.*

----------------------------
#### `app_src` folder
Contains the source code of the game.
Description of these sub-directories:
- `activity` : Contains the `Activity` class which allows the interaction of the different scenes of the game.
- `config`   : Contains the `GameConfig.cpp` file which allows to define the general parameters of the game.
- `gamesystem_ext` : Contains a class derived from `GameSystem` which allows to manipulate game data (save, load, ...).
- `language` : Contains the `GameLanguage.cpp` file which allows to manage everything related to game languages.
- `levels`   : Contains game levels and the `Level.h` file which allows to integrate them into the game.
- `objects`  : Contains the objects that will be used in the different scenes.
- `scenes`   : Contains the different scenes of the game (Introduction, Main menu, ...).

----------------------------
#### `data` folder
Contains game resource files (music, sound sfx, image, ...)

----------------------------
#### `isEngine` folder
Contains the source code of the game engine

---

## How to contribute?
Here are some examples of how to contribute:
- You have developed a module and want it to be part of the engine, you are welcome.
- You have thought of a feature and you want it to be integrated into the engine, do not hesitate to submit it to us with your **name** of course.
- You want to participate in the development of the engine, well welcome to the team!
- You have developed a game or application with the engine, we gladly accept it to publish it!
- You noticed a bug, well done! Let us know Mr. Hacker.

## Contacts
  * For any help or other contribution please contact me on my [email address](mailto:isdaouda.n@gmail.com)
  * You can follow me on Twitter for more informations on my activities [@Is Daouda Games](https://twitter.com/IsDaouda_Games)