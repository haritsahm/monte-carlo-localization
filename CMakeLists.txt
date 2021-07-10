cmake_minimum_required(VERSION 2.8.3)
project(mcl_localization)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)
# set(Qt5_DIR "/opt/qt59/lib/cmake/Qt5")
# set(OpenCV_DIR "/usr/local/share/OpenCV")

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(OpenCV REQUIRED)

set(yaml-cpp_DIR "/usr/local/lib/cmake/yaml-cpp")
find_package(yaml-cpp REQUIRED)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide

set(sources_srcs
    src/mcl_viewer.cpp
    src/mainwindow.cpp
    src/mcl_item.cpp
    src/mcl.cpp
    src/control.cpp
)

set(sources_hpps
    include/mcl_localization/control.h
    include/mcl_localization/mainwindow.h
    include/mcl_localization/mcl.h
    include/mcl_localization/mcl_item.h
    include/mcl_localization/mcl_properties.h
)

set(sources_uis
    ui/control.ui
    ui/mainwindow.ui
)

qt5_wrap_cpp(${PROJECT_NAME}_MOCS ${sources_hpps} ${sources_srcs})
qt5_wrap_ui(${PROJECT_NAME}_UIS_H ${sources_uis})

include_directories(
    include
    include/mcl_localization
    ${YAML_CPP_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${OpenCV_INCLUDE_DIRS}
    )


add_executable(${PROJECT_NAME} ${sources_srcs} ${${PROJECT_NAME}_MOCS} ${sources_uis} ${${PROJECT_NAME}_UIS_H})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES} ${YAML_CPP_LIBRARIES}
    Qt5::Gui
    Qt5::Core
    Qt5::Widgets

    )
