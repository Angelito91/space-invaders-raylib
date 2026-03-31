# Minimun CMake version required
cmake_minimum_required(VERSION 3.10)
project(space-invaders)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib using vcpkg
find_package(raylib CONFIG REQUIRED)

#Colect all .cpp files in src/ automatically
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

#Tell the compiler where to find .h
target_include_directories(${PROJECT_NAME} include) 

# Link raylib to the executable
target_link_libraries(${PROJECT_NAME} raylib)
