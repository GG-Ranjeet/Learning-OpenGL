cmake_minimum_required(VERSION 3.23)

project(
    MeraOpenGL
    VERSION 1.0
    DESCRIPTION "Hello"
    LANGUAGES C CXX
)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(
    CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

file(GLOB SRC_CPP CMAKE_CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/vendor/imgui/*.cpp"
    "src/tests/*.cpp"
)

set(SRC_C "src/glad.c")

add_executable(
    MeraOpenGL
    ${SRC_CPP}
    ${SRC_C}
)

target_include_directories(MeraOpenGL PRIVATE
    include
    src
    src/tests    
)

target_include_directories(MeraOpenGL SYSTEM PRIVATE
    src/vendor/glm
    src/vendor/stb_image
    src/vendor/imgui
)

target_link_directories(MeraOpenGL PRIVATE
    lib
)

target_link_libraries(MeraOpenGL PRIVATE 
    glfw3
    gdi32
    opengl32
)

set_property(TARGET MeraOpenGL PROPERTY CXX_STANDARD 20)

