#cmake

cmake_minimum_required(VERSION 3.5)

set (EZ_SOLUTION_NAME "ezEngine" CACHE STRING "The name of the solution")

project (${EZ_SOLUTION_NAME})

#Clear Targets.txt and Tests.txt
file(WRITE ${CMAKE_BINARY_DIR}/Targets.txt "")
file(WRITE ${CMAKE_BINARY_DIR}/Tests.txt "")

#Clear cached qt dirs
set (Qt5Core_DIR "" CACHE PATH "" FORCE)
set (Qt5Gui_DIR "" CACHE PATH "" FORCE)
set (Qt5Widgets_DIR "" CACHE PATH "" FORCE)
set (Qt5Network_DIR "" CACHE PATH "" FORCE)
set (Qt5WinExtras_DIR "" CACHE PATH "" FORCE)

message (STATUS "Adding SubDirectory 'Code'")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Code)

message (STATUS "Adding SubDirectory 'Projects'")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Projects)

message (STATUS "Adding SubDirectory 'Tools'")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Tools)

message (STATUS "Adding SubDirectory 'Samples'")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Samples)

message (STATUS "Adding SubDirectory 'Games'")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/Games)

message (STATUS "Adding SubDirectory 'UnitTests'")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/UnitTests)