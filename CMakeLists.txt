cmake_minimum_required (VERSION 3.8)
project (AngryTeekkari)

# Target C++ 11 standard (these are optional)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()


# Main target
set(EXECUTABLE_NAME AngryTeekkari)

# Add hpp files
include_directories("include")
include_directories("libs/SFML-2.5.1/include")
include_directories("libs/box2d/include")

# Add source files
file(GLOB SOURCES 
    "src/*.cpp" 
    "src/framework/*.cpp" 
    "src/gameplay/*.cpp"
    "src/screens/*.cpp"
    "src/ui/*.cpp")
add_executable(${EXECUTABLE_NAME} ${SOURCES})



# generate required libraries
add_subdirectory("libs/SFML-2.5.1")
add_subdirectory("libs/box2d")


# link sfml libraries depending on build variant
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${EXECUTABLE_NAME} sfml-system-d sfml-window-d sfml-graphics-d sfml-audio-d)
else()
    target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
endif()


# link box2d
target_link_libraries(${EXECUTABLE_NAME} box2d)


# specify to copy library binaries to executable directory
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/libs/SFML-2.5.1/lib/\$\(Configuration\)"
        "${CMAKE_CURRENT_BINARY_DIR}/\$\(Configuration\)")

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/libs/box2d/bin/\$\(Configuration\)"
        "${CMAKE_CURRENT_BINARY_DIR}/\$\(Configuration\)")
        


# specify to copy data folder to executable directory
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "${CMAKE_CURRENT_BINARY_DIR}/\$\(Configuration\)/data")