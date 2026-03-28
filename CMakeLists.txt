cmake_minimum_required(VERSION 3.10)
project(space-invaders)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar raylib usando vcpkg
find_package(raylib REQUIRED)

# Agregar el ejecutable
add_executable(${PROJECT_NAME} src/main.cpp)

# Enlazar raylib
target_link_libraries(${PROJECT_NAME} raylib)
