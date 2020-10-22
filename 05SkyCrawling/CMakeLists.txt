cmake_minimum_required(VERSION 3.5)
project(SkyCrawling VERSION 0.1.0)


# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

add_executable(SkyCrawling main.cpp)

# FIXME: These paths are hard written in CMakeLists.
# FIXED: Configure the variables through -D option in cmake
# if (GLUT_ROOT_PATH)
#     message("found GLUT root path")
# else()
#     message("GLUT not found.")
#     set(GLUT_ROOT_PATH "D:/bin/freeglut/")
#     set(OPENGL_LIBRARY_DIR "D:/bin/freeglut/lib/")
# endif()

# search for GLUT installed on the system, see FindGLUT.cmake for the macros
find_package(GLUT REQUIRED)
if (GLUT_FOUND)
    message("GLUT found.")
    include_directories(AFTER ${GLUT_INCLUDE_DIR})
    message("GLUT include: ${GLUT_INCLUDE_DIR}")
    # TODO: figure out what these lines do. Seems link_directories() is deprecated.
    # link_directories(AFTER ${GLUT_LIBRARIES})
    # target_include_directories(HelloGL PUBLIC ${GLUT_INCLUDE_DIR})
    target_link_libraries(SkyCrawling
        GLUT::GLUT)
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
    target_link_libraries(SkyCrawling
        OpenGL::GL
        OpenGL::GLU)
    message("OpenGL library: ${OPENGL_LIBRARIES}")
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

