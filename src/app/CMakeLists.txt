file(GLOB MAIN_SOURCE_FILES . *.cpp)
#If any UI is here :
file(GLOB UIs . *.ui)

add_executable (application ${MAIN_SOURCE_FILES} ${UIs} ../../res.qrc)

find_package (Qt5Core REQUIRED)
find_package (Qt5Gui REQUIRED)
find_package (Qt5Widgets REQUIRED)

target_link_libraries (application Qt5::Core)
target_link_libraries (application Qt5::Gui)
target_link_libraries (application Qt5::Widgets)
target_link_libraries (application helpers)
target_link_libraries (application opengl_utils)


