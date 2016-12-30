file(GLOB TEST_FILES . *.cpp)

add_executable (tests ${TEST_FILES})

#To add tests of a specific lib, do this :
#target_link_libraries (tests <NameOfLib>)

find_package (Qt5Core REQUIRED)
target_link_libraries (tests Qt5::Core)

target_include_directories (tests  PUBLIC "${CMAKE_SOURCE_DIR}/src")
