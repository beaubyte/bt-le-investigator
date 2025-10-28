cmake_minimum_required(VERSION 3.16)

project(bt-le-investigator LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Bluetooth)

add_executable(bt-le-investigator
  main.cpp
  BluetoothControl.h
)
target_link_libraries(bt-le-investigator Qt${QT_VERSION_MAJOR}::Core Qt6::Bluetooth)
include(GNUInstallDirs)
install(TARGETS bt-le-investigator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
