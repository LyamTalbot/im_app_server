cmake_minimum_required(VERSION 3.30.5)  # CMake version check
set(CMAKE_TOOLCHAIN_FILE "/Users/lyamtalbot/.vcpkg-clion/vcpkg/scripts/buildsystems" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_BUILD_TYPE debug)


include_directories("/Users/lyamtalbot/.vcpkg-clion/vcpkg/installed/arm64-osx/include")

project(im_app_server)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard
# Add main.cpp file of the project root directory as a source file
find_package(Poco REQUIRED Net Foundation Util)
set(SOURCE_FILES main.cpp
        im_auth.h
        im_auth.cpp
        im_app_structs.h
        shared_mutexes.hpp
        shared_mutexes.cpp
        user_socket_map.hpp
        user_socket_map.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(im_app_server ${SOURCE_FILES})
target_link_libraries(im_app_server PRIVATE Poco::Net Poco::Foundation Poco::Util)