cmake_minimum_required(VERSION 3.5)

# set the title of the project
project(Ellipse)

# create an Executable, the name is the same with the project.
add_executable(test
    src/ellipse.cpp
    src/Geometry.cpp
    src/graphics.cpp
    src/ppm.cpp
)

target_include_directories(test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)