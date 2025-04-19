cmake_minimum_required(VERSION 3.16)

project(test_route_plan LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(test_route_plan
  test/test_route_plan.cpp
  src/route_plan.cpp
  include/route_plan.h
  data/map_of_bupt.geojson


)

target_include_directories(test_route_plan PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(test_route_plan Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS test_route_plan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
