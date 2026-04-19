cmake_minimum_required(VERSION 3.12)
project(space-invaders VERSION 0.1 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Export compile commands for clang-tidy and other tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Allow out-of-tree builds
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(STATUS "Warning: building in-source. It's recommended to use an out-of-source build (cmake -B build).")
endif()

# Prefer the raylib provided by vcpkg if available via CONFIG mode
find_package(raylib CONFIG REQUIRED)

# Find OpenGL (for linking GL on Linux)
find_package(OpenGL REQUIRED)

# Try to locate glfw3 via CMake config mode (useful when provided by vcpkg)
find_package(glfw3 CONFIG QUIET)

# Collect sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Include headers
target_include_directories(${PROJECT_NAME} PRIVATE include include/core include/entities)

# Link raylib first (it may be an imported target or an alias)
# Some raylib builds expose an imported target (raylib::raylib); fall back to plain 'raylib' if not present.
if(TARGET raylib::raylib)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib::raylib)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()

# Link OpenGL
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# If we found a glfw CMake package, link its target (the target name can vary; try common ones)
if(TARGET glfw)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
elseif(TARGET glfw3::glfw)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw3::glfw)
elseif(glfw3_FOUND)
    # If find_package(glfw3) set variables, try the imported target names
    if(TARGET glfw3)
        target_link_libraries(${PROJECT_NAME} PRIVATE glfw3)
    endif()
endif()

# On Unix platforms (Linux) static raylib may require explicit platform libraries.
if(UNIX AND NOT APPLE)
    # Common system libraries needed for windowing/GL when linking static libs (X11, Xrandr, Xxf86vm, Xinerama, Xcursor, GL, pthread, dl, m, rt)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        dl
        m
        pthread
        rt
        X11
        Xrandr
        Xxf86vm
        Xinerama
        Xcursor
        # GL already linked via OpenGL::GL but keep GL entry for compatibility with some toolchains
        GL
    )
endif()

# On macOS, link Cocoa, IOKit, CoreVideo frameworks if needed by raylib (often handled by the raylib package)
if(APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(COREVIDEO_FRAMEWORK CoreVideo)
    if(COCOA_FRAMEWORK)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${COCOA_FRAMEWORK})
    endif()
    if(IOKIT_FRAMEWORK)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${IOKIT_FRAMEWORK})
    endif()
    if(COREVIDEO_FRAMEWORK)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${COREVIDEO_FRAMEWORK})
    endif()
endif()

# Helpful RPATH handling for runtime with vcpkg on Linux
if(UNIX)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH TRUE
    )
endif()

# Optionally install the binary (useful for CI packaging)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
