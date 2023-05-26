cmake_minimum_required(VERSION 3.2)
project(QtWidgetExProject)

add_subdirectory(QtWidgetEx)
add_subdirectory(QtWidgetExPlugin)

option(WIDGETEX_BUILD_TEST "enable qtwidgetex test project" OFF)

if (WIDGETEX_BUILD_TEST)
    add_subdirectory(test)
endif ()