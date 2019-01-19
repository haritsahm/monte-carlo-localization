cmake_minimum_required(VERSION 2.8.3)
project(mcl_viewer)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(Qt5_DIR "/opt/qt59/lib/cmake/Qt5")
set(OpenCV_DIR "/usr/local/share/OpenCV")

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(OpenCV REQUIRED)
find_package(yaml-cpp REQUIRED)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide

include_directories(
    ${YAML_CPP_INCLUDE_DIR}
    )

add_executable(${PROJECT_NAME} mcl_viewer.cpp mainwindow.cpp
    mainwindow.ui control.ui mcl_item.cpp mcl_properties.h mcl.cpp
    control.cpp
    )


target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES} ${YAML_CPP_LIBRARIES}
    Qt5::Gui
    Qt5::Core
    Qt5::Widgets
    )
