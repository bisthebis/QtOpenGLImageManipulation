file(GLOB OPENGL_UTILS_SOURCES . *.cpp)


add_library (opengl_utils ${OPENGL_UTILS_SOURCES})

find_package (Qt5Core REQUIRED)
find_package (Qt5Gui REQUIRED)

target_link_libraries (opengl_utils Qt5::Core)
target_link_libraries (opengl_utils Qt5::Gui)
target_link_libraries (opengl_utils helpers)
