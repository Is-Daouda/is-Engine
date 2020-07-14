# CMake
**is::Engine** for [CMake](https://cmake.org/).
This project allows you to compile the is::Engine game engine with the CMake tool.

---

## Prerequisites

- [SFML Library](https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip) (2.5 +)
- CMake (3.1 +)
- GCC Compiler (7.3 +)

---

## Installation

### Windows
- Compile SFML with CMake to have **static libraries** and put on **C:/** (C:/SFML)
- Move the *CMake project* of is::Engine to your **C:/** (C:/CMake)
- Execute this command :
```bash
cmake -S "C:/CMake" -B "C:/build"
cd build
make
```

### Linux
- Install SFML 2.5.1 on your machine
- Move the CMake project of is::Engine to **/home/user/** (/home/user/CMake)
- Execute this command :
```bash
sudo cmake -S "CMake" -B "build"
cd build
sudo make
```

## After installation
You will have a **bin** folder in which the engine demo is located.

**Enjoy!**