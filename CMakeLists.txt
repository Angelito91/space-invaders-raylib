cmake_minimum_required(VERSION 3.10)

# Configuración recomendada para Windows 64-bit (w64devkit, raylib)
if(WIN32 AND NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "C:/raylib/w64devkit/bin/gcc.exe" CACHE FILEPATH "C compiler" FORCE)
endif()
if(WIN32 AND NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "C:/raylib/w64devkit/bin/g++.exe" CACHE FILEPATH "C++ compiler" FORCE)
endif()

project(space-invaders LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Preferencias de raylib (override con variables de entorno o -D en CMake)
set(RAYLIB_DEVKIT_ROOT $ENV{RAYLIB_DEVKIT_ROOT})
if(NOT RAYLIB_DEVKIT_ROOT)
    set(RAYLIB_DEVKIT_ROOT "C:/raylib/w64devkit/x86_64-w64-mingw32")
endif()

set(RAYLIB_INCLUDE_DIR $ENV{RAYLIB_INCLUDE_DIR})
if(NOT RAYLIB_INCLUDE_DIR)
    set(RAYLIB_INCLUDE_DIR "C:/raylib/raylib/src")
endif()

set(RAYLIB_LIBRARY $ENV{RAYLIB_LIBRARY})
if(NOT RAYLIB_LIBRARY)
    set(RAYLIB_LIBRARY "${RAYLIB_DEVKIT_ROOT}/lib/libraylib.a")
endif()

message(STATUS "Raylib include: ${RAYLIB_INCLUDE_DIR}")
message(STATUS "Raylib library: ${RAYLIB_LIBRARY}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "CXX compiler: ${CMAKE_CXX_COMPILER}")

if(NOT EXISTS "${RAYLIB_LIBRARY}")
    message(FATAL_ERROR "No se encontró libraylib.a en ${RAYLIB_LIBRARY}. Instala raylib para w64devkit o ajusta RAYLIB_DEVKIT_ROOT/RAYLIB_LIBRARY.")
endif()

add_library(raylib STATIC IMPORTED GLOBAL)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION "${RAYLIB_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${RAYLIB_INCLUDE_DIR}"
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "${RAYLIB_INCLUDE_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE raylib opengl32 gdi32 winmm)

