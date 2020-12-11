cmake_minimum_required(VERSION 3.5)
project(UFO VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/include)

# search for GLUT installed on the system, see FindGLUT.cmake for the macros
find_package(GLUT REQUIRED)
if (GLUT_FOUND)
    message("GLUT found.")
    include_directories(AFTER ${GLUT_INCLUDE_DIR})
    message("GLUT include: ${GLUT_INCLUDE_DIR}")
    # TODO: figure out what these lines do. Seems link_directories() is deprecated.
    # link_directories(AFTER ${GLUT_LIBRARIES})
    # target_include_directories(HelloGL PUBLIC ${GLUT_INCLUDE_DIR})
    
    link_libraries(GLUT::GLUT) # link_libraries could only have effects on the targets added later.
    
    message("GLUT library: ${GLUT_LIBRARIES}")
else()
    message(FATAL_ERROR "GLUT not found!")
endif()

# OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message("OpenGL found.")
    include_directories(AFTER ${OPENGL_INCLUDE_DIR})
    # target_include_directories(HelloGL PUBLIC ${OPENGL_INCLUDE_DIR})
    message("OpenGL include: ${OPENGL_INCLUDE_DIR}")
    # link_directories(AFTER ${OPENGL_LIBRARIES})
    link_libraries(
        OpenGL::GL
        OpenGL::GLU)
    message("OpenGL library: ${OPENGL_LIBRARIES}")
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

add_executable(UFO
    # include/geometry.h
    # include/astroid.h
    src/Astroid.cpp
    src/geometry.cpp
    src/UFO.cpp
    src/main.cpp
)