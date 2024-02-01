# PDL 2.0 Sample demo with CMake built in Ubuntu 20.04

## General description
  * Built a cross-platform app that can be run on any kind of OS (MacOS, Linux, Windows, etc...)
  * Use as a template for any project that utitlise SDL2.0

## Requirement packages
* g++ in Linux **Ubuntu** 

`sudo apt-get install g++`

* [SDL2][]

`sudo apt-get install libsdl2-dev`

* [CMake][] (used to compile the entire file if using CMakeLists)

`sudo apt-get install cmake`

* SDL2 add-ons libraries (**OPTIONAL**, *only installed if you want to work with those extended libraries*)

`sudo apt install libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev libsdl2-gfx-dev`

 
## Usage

* Please run in **order**:

```sh
mkdir build

cd build

cmake ..

make

./sdl_demo
```

## Notes

To run this project in VSCode with CMake extension enabled, you should configure CMake to use 'UNIX Makefiles'
for generator by configuring in USER settings.json:

```json
"C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",

"cmake.generator": "Unix Makefiles",
```

![](https://github.com/lenhatquang2512/sdl2_music_project/blob/main/fso.png)

<!-- ![](https://github.com/lenhatquang2512/fso_training_CPP_Code_test/blob/master/fso.png) -->

**Please give us a Star if you find this helpful !**

[CMake]: https://cmake.org
[SDL2]: https://www.libsdl.org