
set(SOURCES
  "main.cpp"
  "window.cpp"
  "graphics.cpp"
  "square_rubber_band.cpp"
  "square_rubber_band.hpp"
  "window.hpp"
  "graphics.hpp"
)

add_executable(fractal "${SOURCES}")

set_target_properties(
  fractal PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
# Qt library
set_target_properties(fractal PROPERTIES
        CMAKE_AUTOMOC ON
        CMAKE_AUTORCC ON
        CMAKE_AUTOTIC ON
)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(fractal Qt5::Widgets)

## Enable qthread
set_target_properties(fractal PROPERTIES
  CMAKE_CXX_FLAGS -pthread
)

set(CMAKE_CXX_FLAGS -pthread)

