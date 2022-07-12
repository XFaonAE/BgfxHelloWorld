cmake_minimum_required(VERSION 3.0)
project(BgfxHelloWorld)

add_executable(app src/main.cxx)

add_subdirectory(deps/bkaradzic/bgfx.cmake)
include_directories(deps/bkaradzic/bgfx.cmake)

add_subdirectory(deps/glfw/glfw)
include_directories(deps/glfw/glfw)

target_link_libraries(app bgfx glfw bx)
