cmake_minimum_required(VERSION 3.13)

project(Fractal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(external/Complex)
target_link_libraries(fractal complex)
