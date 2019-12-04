
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOTIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
  "main.cpp"
  "window.cpp"
  "graphics.cpp"
)

set(HEADERS
  "window.hpp"
  "graphics.hpp"
)

add_executable(fractal "${SOURCES}")
target_sources(fractal PRIVATE "${HEADERS}")

target_link_libraries(fractal Qt5::Widgets)

set_target_properties(
  fractal PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

