cmake_minimum_required(VERSION 3.24)
project(Sapper)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ABSOLUTE_DESTINATION_FILES ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_AUDIO OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.0
)
FetchContent_MakeAvailable(SFML)


add_executable(Main main.cpp Field.cpp Play.cpp Board.cpp Field.cpp WindowGen.cpp)

target_link_options(Main PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})

target_link_libraries(
        Main
        sfml-graphics
        sfml-main
)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Image
        ${PROJECT_BINARY_DIR}/Image
        COMMENT "Copying resources into binary directory")

add_dependencies(Main copy_resources)