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

# Set files used to compile
set(SOURCES "src/main.cpp")

# Set (.exe name) & (files used to compile)
add_executable(${PROJECT_NAME} ${SOURCES})

# Determine output type [at configure, NOT build]
if(EMSCRIPTEN) # emscripten (web build)
    
    message(STATUS "===== CONFIGURING FOR EMSCRIPTEN WEB BUILD =====")

else() # native build

    message(STATUS "===== CONFIGURING FOR NATIVE EXE BUILD =====")

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
endif()