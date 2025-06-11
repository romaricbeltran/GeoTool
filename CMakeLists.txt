cmake_minimum_required(VERSION 3.20)
project(GeoTool VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_policy(SET CMP0135 NEW)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)
target_compile_definitions(glad PRIVATE GLAD_GLAPI_EXPORT_BUILD)

if(MSVC)
    target_compile_options(glad PRIVATE /w)
endif()

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

if(MSVC)
    target_compile_options(imgui PRIVATE /w)
endif()

# GoogleTest
include(FetchContent)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(CMAKE_CXX_FLAGS_BACKUP ${CMAKE_CXX_FLAGS})
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w")
endif()

FetchContent_MakeAvailable(googletest)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_BACKUP})

# Main executable
add_executable(GeoTool src/main.cpp)
target_include_directories(GeoTool PUBLIC
        external/glfw/include
        external/glad/include
        external/glm
)
target_link_libraries(GeoTool PRIVATE glad glfw imgui opengl32)
target_compile_features(GeoTool PRIVATE cxx_std_20)

# Tests executable
add_executable(GeoToolTests tests/main_tests.cpp)
target_include_directories(GeoToolTests PUBLIC
        external/glfw/include
        external/glad/include
        external/glm
)
target_link_libraries(GeoToolTests PRIVATE gtest_main glad glfw imgui opengl32)
target_compile_features(GeoToolTests PRIVATE cxx_std_20)

enable_testing()
include(GoogleTest)
gtest_discover_tests(GeoToolTests)

if(MSVC)
    target_compile_options(GeoTool PRIVATE /W4 /permissive- /WX /utf-8)
    target_compile_options(GeoToolTests PRIVATE /W4 /permissive- /WX /utf-8)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
