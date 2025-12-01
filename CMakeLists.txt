cmake_minimum_required(VERSION 3.16)

project(bt-le-investigator LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Bluetooth Sql)

add_executable(bt-le-investigator
  main.cpp

  discovery.h discovery.cpp
  devicebox.h devicebox.cpp
  macdatabase.h macdatabase.cpp





)
target_link_libraries(bt-le-investigator Qt${QT_VERSION_MAJOR}::Core Qt6::Bluetooth Qt6::Sql)
include(GNUInstallDirs)
install(TARGETS bt-le-investigator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
