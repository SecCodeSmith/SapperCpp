cmake_minimum_required(VERSION 3.24)
project(Sapper)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

add_executable(Main main.cpp Play.h Field.cpp Play.cpp Play.h Board.cpp Field.cpp WindowGen.cpp WindowGen.h)

target_link_libraries(
        Main
        sfml-graphics
)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Image
        ${PROJECT_BINARY_DIR}/Image
        COMMENT "Copying resources into binary directory")

add_dependencies(Main copy_resources)