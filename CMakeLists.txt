cmake_minimum_required(VERSION 3.20)
project(GeoTool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GLFW
add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

# ImGui
file(GLOB IMGUI_SRC
        external/imgui/*.cpp
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
        external/imgui
        external/imgui/backends
        external/glfw/include
)

# Main source
set(SOURCES src/main.cpp)
add_executable(GeoTool ${SOURCES})

# Includes
target_include_directories(GeoTool PUBLIC
        external/glfw/include
        external/glad/include
        external/glm
)

# Link libs
target_link_libraries(GeoTool glad glfw imgui opengl32)

# Avoid some Glad warnings
target_compile_definitions(glad PRIVATE GLAD_GLAPI_EXPORT_BUILD)

# Strict : warnings = errors
if(MSVC)
    target_compile_options(GeoTool PRIVATE /W4 /permissive- /WX)
endif()
