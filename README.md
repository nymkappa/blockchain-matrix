### Udacity rubric checklist (completed ones)

* ✔️ `README (All Rubric Points REQUIRED)`
* ✔️ `Compiling and Testing (All Rubric Points REQUIRED)`
* `Loops, Functions, I/O`
  * ✔️ `The project demonstrates an understanding of C++ functions and control structures.`
  * ✔️ `The project reads data from a file and process the data, or the program writes data to a file.`. While we don't really use files much in this project, we do load a .png file and read data from a websocket. Part of the code was taken online and proplery credited.
  * ✔️ `The project accepts user input and processes the input.`. The project does not require any user interaction. The only interaction the user can have is to close the window, which is properly processed in the main loop to cleanup the program before the end of its execution.
* `Object Oriented Programming`
  * ✔️ `The project uses Object Oriented Programming techniques.`
  * ✔️ `Classes use appropriate access specifiers for class members.`
  * ✔️ `Class constructors utilize member initialization lists.` -> `TransactionEvent.hpp:10`
  * ✔️ `Classes abstract implementation details from their interfaces.`
  * ✔️ `Classes encapsulate behavior.`
  * ✔️ `Classes follow an appropriate inheritance hierarchy.` -> `TransactionEvent` inherits from `AEvent`. `App` and `Backend` are composed with `EventQueue` using a shared_ptr.
  * 🚫 `Overloaded functions allow the same function to operate on different parameters.` -> Not used is this program
  * ✔️ `Derived class functions override virtual base class functions.` -> `TransactionEvent` inherits from `AEvent` using virtual keyword to override the default behavior.
  * 🚫 `Templates generalize functions in the project.` -> Not used is this program
  * ✔️ `The project makes use of references in function declarations.` -> `App.hpp:25` / `Renderer.cpp:126`
  * ✔️ `The project uses destructors appropriately.` -> `Renderer.hpp:52`
  * ✔️ `The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.` -> `Renderer.hpp` is a good example. It initialize SDL rendering core, holds pointers on the required data, and cleanup everything automatically in the destructor. Only the `EventQueue` is allocated on the heap, using a shared_ptr. Everything else that is not handled by 3rd party is managed on the stack for easier memory management.
  * ✔️ `The project follows the Rule of 5.` -> Implemented in `Symbol`
  * ✔️ `The project uses move semantics to move data, instead of copying it, where possible.` -> Example in `Backend.cpp:129`
  * ✔️ `The project uses smart pointers instead of raw pointers.` -> `App` and `Backend` are sharing a shared_ptr on `EventQueue`. Raw pointers are managed by SDL library.
* Concurrency
  * ✔️ `The project uses multiple threads in the execution.` -> The program uses two threads. Second thread is created at `App.cpp:55`
  * 🚫 `A promise and future is used in the project.` -> Not used is this program
  * ✔️ `A mutex or lock is used in the project.` -> `EventQueue.hpp` uses mutex to sync threads
  * 🚫 `A condition variable is used in the project.` -> Not used is this program






# Bitcoin live transaction visualizer

Expected output:

![image](https://user-images.githubusercontent.com/9780671/111024548-bed02a80-8422-11eb-99f0-9d2b9f26e897.png)

A real time visualizer of blockchain transactions. Each Bitcoin represents a new transaction on the network.

When you run the program, it will attempt to connect on blockchain.com websocket and start listening for new broadcasted bitcoin transaction. It may be possible that the websocket does not send any data for a while so please patient.

When you close the application window, the backend thread may still be waiting for data. Once the last piece of data is received, the backend thread will end and the application will exit gracefully.

## Dependencies for Running Locally

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, running `sudo apt-get install libsdl2-dev` will do the trick.
* SDL2_image >= 2.0
  * Doc can be found [here](https://www.libsdl.org/projects/SDL_image/)
  * Note that for Linux, running `sudo apt-get install libsdl2-image-dev` will do the trick.
* OpenSSL >= 1.1
  * All installation instructions can be found [here](https://wiki.openssl.org/index.php/Compilation_and_Installation)
  * Note that for Linux, running `sudo apt-get install libssl-dev` will do the trick.
* Boost + Beast
  * [Windows + Linux] - Just download boost from [here](https://www.boost.org/users/download/) and extract it to the project root in a "boost" folder.
  * Linux guide - Install Boost in the project, [here](https://www.boost.org/doc/libs/1_75_0/more/getting_started/unix-variants.html)
  * Windows guide - Install Boost in the project, [here](https://www.boost.org/doc/libs/1_75_0/more/getting_started/windows.html)
  * Beast is already provided in the repository, but you can replace it if needed by get the file from [githubg](https://github.com/boostorg/beast.git)

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
  * `libpng16-16.dll`
  * `zlib1.dll`
* OpenSSL
  * `libssl-1_1-x64.dll`
  * `libcrypto-1_1-x64.dll`

On Windows, your `build\Debug` folder should look like this

![image](https://user-images.githubusercontent.com/9780671/111022182-92adad00-8414-11eb-9196-99b14cec4de6.png).

On Linux, your `build` folder should look like this

![image](https://user-images.githubusercontent.com/9780671/111022234-df918380-8414-11eb-9ae0-84eac748bd5d.png)


Before running the application, copy `btc.png` next to the compiled executable.

You should be good to go now :).

## Code structure

The source code of this applicationc can be found in `src` folder.

The entry point is `main.cpp`

The main class is `App` and it contains the main thread loop, which is responsible for SDL initialization and event polling. It also use a `Renderer` object is its `App::Run*()` function to handle the rendering.

The `Backend` class is used for listening to the websocket and pushing events in the `EventQueue` which is then processed by the main thread to create new Bitcoin sprite.

`Symbol` holds the Bitcoin sprites data and update its own position every frame.
