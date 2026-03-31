cmake_minimum_required(VERSION 3.10)
project(space-invaders)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Buscar raylib
find_package(raylib CONFIG REQUIRED)

# 2. Agregar el ejecutable
add_executable(${PROJECT_NAME} src/main.cpp)

# 3. Enlazar raylib y sus dependencias de Linux
# Nota: Usamos raylib::raylib (el target oficial de vcpkg)
target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    X11
    GL
    m
    pthread
    dl
    rt
)
