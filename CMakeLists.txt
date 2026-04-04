cmake_minimum_required(VERSION 3.15)

project(space-invaders LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ============================================
# Configuración de Raylib
# ============================================
set(RAYLIB_INCLUDE_DIR "C:/raylib/raylib/src")
set(RAYLIB_LIB_DIR "C:/raylib/w64devkit/x86_64-w64-mingw32/lib")

# Validar raylib
if(NOT EXISTS "${RAYLIB_INCLUDE_DIR}/raylib.h")
    message(FATAL_ERROR "No se encontró raylib.h en ${RAYLIB_INCLUDE_DIR}")
endif()

find_library(RAYLIB_LIBRARY
    NAMES raylib
    PATHS "${RAYLIB_LIB_DIR}"
    NO_DEFAULT_PATH
    REQUIRED
)

message(STATUS "Raylib include: ${RAYLIB_INCLUDE_DIR}")
message(STATUS "Raylib library: ${RAYLIB_LIBRARY}")

# ============================================
# Archivos fuente del proyecto (POO)
# ============================================
set(SOURCE_FILES
    src/main.cpp
    src/Game.cpp
    src/AssetManager.cpp
    src/EntityManager.cpp
    src/Player.cpp
    src/Alien.cpp
    src/Bullet.cpp
    src/BarrierBlock.cpp
)

# ============================================
# Crear ejecutable
# ============================================
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# ============================================
# Incluir directorios
# ============================================
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${RAYLIB_INCLUDE_DIR}
)

# ============================================
# Librerías del sistema
# ============================================
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${RAYLIB_LIBRARY}
    opengl32
    gdi32
    winmm
)

# ============================================
# Información de compilación
# ============================================
message(STATUS "========================================")
message(STATUS "Space Invaders - Compilación POO")
message(STATUS "========================================")
message(STATUS "Proyecto: ${PROJECT_NAME}")
message(STATUS "Estándar: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Archivos: ${SOURCE_FILES}")
message(STATUS "Compilación: cmake --build .")
message(STATUS "========================================")


