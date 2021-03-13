# Bitcoin live transaction visualizer

A real time visualizer of blockchain transactions. Each Bitcoin represents a new transaction on the network.

## Dependencies for Running Locally

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_image >= 2.0
  * Doc can be found [here](https://www.libsdl.org/projects/SDL_image/)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* OpenSSL >= 1.1
  * All installation instructions can be found [here](https://wiki.openssl.org/index.php/Compilation_and_Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred
* Boost + Beast
  * Install boost dependency `git clone --branch boost-1.75.0 https://github.com/boostorg/boost.git`
  * Install beast dependency `git clone --branch boost-1.75.0 https://github.com/boostorg/beast.git`
  * You can just clone the source code direclty in the root folder or install it on your system

## Build

* `mkdir build`
* `cd build`
* `cmake ..`
* Compile
  * Linux: `make`
  * Windows: Open the .sln project and compile using Visual Studio Community 2019+ or use Visual Studio Code with CMake extensions

## Run

If you are Windows, before running the application you will need to copy all the requires .dll next to the generated .exe file:

* SDL
  * `SDL2.dll`
* SDL_Image
  *`libjpeg-9.dll`
  * `libpng16-16.dll`
  * `libtiff-5.dll`
  * `libwebp-7.dll`
  * `zlib1.dll`
* OpenSSL
  * `libssl-1_1-x64.dll`
  * `libcrypto-1_1-x64.dll`

Before running the application, copy `btc.png` next to the compiled executable.

You should be good to go now :).