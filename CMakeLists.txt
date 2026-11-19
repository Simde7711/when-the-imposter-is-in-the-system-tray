# -------------------- Basic Setup --------------------
cmake_minimum_required(VERSION 3.15)                # Minimum required CMake version
project(ImposterSystemTray)                         # Project name

set(CMAKE_CXX_STANDARD 20)                          # Use C++20
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)               # Generate compile_commands.json (useful for clangd, LSPs)

# Debug flags: disable optimizations, enable debug info
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

# Static link libstdc++/libgcc for MinGW builds (optional, avoids DLLs)
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# -------------------- Build Setup --------------------

# Move icon file
configure_file(
    icon.ico 
    ./
    COPYONLY
)

# Collect all .cpp files in src/ recursively
file(
    GLOB_RECURSE 
    SRC_FILES 
    src/*.cpp
)

# Define the executable target
add_executable(
    ${PROJECT_NAME} 
    ${SRC_FILES}
    imposterSystemTray.rc
)

# Add options to the executable
if(WIN32) 
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
endif()

# Include directories for this target
# target_include_directories(${PROJECT_NAME} PRIVATE
#     ${CMAKE_SOURCE_DIR}/include            # Your own project headers
# )