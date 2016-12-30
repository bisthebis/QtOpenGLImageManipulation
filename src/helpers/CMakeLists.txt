file(GLOB HELPERS_SOURCES . *.cpp)


add_library (helpers ${HELPERS_SOURCES})

find_package (Qt5Core REQUIRED)
find_package (Qt5Gui REQUIRED)

target_link_libraries (helpers Qt5::Core)
target_link_libraries (helpers Qt5::Gui)
