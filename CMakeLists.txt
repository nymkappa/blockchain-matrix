cmake_minimum_required(VERSION 3.7)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

add_definitions(-DBOOST_DATE_TIME_NO_LIB)
add_definitions(-D_WIN32_WINDOWS)
add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)

project(BlockchainMatrix)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SDL2_DIR "./SDL")
find_package(SDL2 REQUIRED)

set(SDL2_IMAGE_PATH "./SDL_image")
find_package(SDL2_image REQUIRED)

set(OPENSSL_ROOT_DIR "./openssl")
find_package(OpenSSL REQUIRED)

set(Boost_INCLUDE_DIR "./boost")
find_package(Boost)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS}
    "./boost_1_75_0/" "./beast/include/" src)

add_executable(BlockchainMatrix src/main.cpp "src/root_certificates.hpp" "src/App.hpp" "src/App.cpp" "src/SDLException.hpp" "src/Backend.hpp" "src/Backend.cpp" "src/Renderer.hpp" "src/Renderer.cpp" "src/Symbol.hpp" "src/Symbol.cpp")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

if (UNIX)
    target_link_libraries(BlockchainMatrix ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${OPENSSL_LIBRARIES} "pthread")
endif (UNIX)

if (WIN32)
    target_link_libraries(BlockchainMatrix ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${OPENSSL_LIBRARIES})
endif(WIN32)