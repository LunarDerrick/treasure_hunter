# Command:
# 1. VSCode -> Command Palette
# 2. [only if you modify CMakeLists.txt] CMake: Configure
# 3. Ensure "build" folder has "CMakeFiles"
# 4. CMake: Build
# 5. Verify "TreasureHunter.exe" is in "build" folder

# Set compiler policy
cmake_minimum_required(VERSION 3.16)

# Set compile features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE) # ensure consistent versioning

# Set project name
project(TreasureHunter)

# Define source groups
set(CORE_SOURCES
    "src/core/game.cpp"
    "src/core/game.h"
)

set(ENTITY_SOURCES
    "src/entity/player.cpp"
    "src/entity/player.h"
)

set(SCENE_SOURCES
    "src/scene/zone.cpp"
)

set(UTIL_SOURCES
    "src/util/asset_loader.cpp"
)

# Set files used to compile
set(SOURCES 
    "src/main.cpp"
    ${CORE_SOURCES}
    ${ENTITY_SOURCES}
    ${SCENE_SOURCES}
    ${UTIL_SOURCES}
)

# Set (.exe name) & (files used to compile)
add_executable(${PROJECT_NAME} ${SOURCES})

# Declare external library
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL3-3.2.18") # initialize filepath
find_package(SDL3 REQUIRED) # locate "%SDL3%.cmake" files

# Include external library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3) # utilize library (list of "%SDL3%" files/classes)

# Copy important data files to build
add_custom_target(
    copy_sdl_dll # command name
    ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Adding .dll file to build"
)

# Copy game assets to build directory
add_custom_target(
    copy_assets
    ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/asset"
        "${CMAKE_CURRENT_BINARY_DIR}/asset"
    COMMENT "Copying game assets to build"
)
