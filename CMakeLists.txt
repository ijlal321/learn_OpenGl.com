cmake_minimum_required(VERSION 3.15)
project(learnOpengl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##  Variables Definition
# ==========================================
set(Glad_Dir "${CMAKE_SOURCE_DIR}/external/glad")
set(Glfw_dir "${CMAKE_SOURCE_DIR}/external/glfw")

##  Main Project Files
# ==========================================
add_executable(learnOpengl
                src/main.cpp
                src/Shader.cpp
                src/stb_image.cpp
                )


target_include_directories(learnOpengl PRIVATE ${CMAKE_SOURCE_DIR}/include)

## Linking Opengl
target_link_libraries(learnOpengl PRIVATE opengl32)

## Adding Glad Files for Opengl Extensions
# ==========================================
target_include_directories(learnOpengl PRIVATE ${Glad_Dir}/include)
target_sources(learnOpengl PRIVATE ${Glad_Dir}/src/glad.c)

## Adding Glfw Files for Screen
# ==========================================
target_include_directories(learnOpengl PRIVATE ${Glfw_dir}/include)
target_link_libraries(learnOpengl PRIVATE ${Glfw_dir}/lib-vc2022/glfw3.lib)

## Adding Glad Files for GLM Library
# ==========================================
target_include_directories(learnOpengl PRIVATE ${CMAKE_SOURCE_DIR}/external/glm)
