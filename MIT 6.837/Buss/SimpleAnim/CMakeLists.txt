cmake_minimum_required(VERSION 3.0)

PROJECT(main)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(main ${DIR_SRCS})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} m)