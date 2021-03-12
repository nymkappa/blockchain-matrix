cmake_minimum_required(VERSION 3.7)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

add_definitions(-DBOOST_DATE_TIME_NO_LIB)
add_definitions(-D_WIN32_WINDOWS)
add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)

project(BlockchainMatrix)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SDL2_DIR "./SDL2-2.0.14")
find_package(SDL2 REQUIRED)

set(OPENSSL_ROOT_DIR "./openssl")
find_package(OpenSSL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} "./boost_1_75_0/" "./beast/include/" src)

add_executable(BlockchainMatrix src/main.cpp "src/root_certificates.hpp" "src/App.hpp" "src/App.cpp" "src/SDLException.hpp" "src/Backend.hpp" "src/Backend.cpp" "src/Renderer.hpp" "src/Renderer.cpp" "src/Symbol.hpp" "src/Symbol.cpp")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(BlockchainMatrix ${SDL2_LIBRARIES} ${OPENSSL_LIBRARIES})
