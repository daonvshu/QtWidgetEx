cmake_minimum_required(VERSION 3.12)
project(QtWidgetExProject)

add_subdirectory(QtWidgetEx)

option(WIDGETEX_BUILD_PLUGIN "enable qtwidgetex designer plugin" ON)

if (WIDGETEX_BUILD_PLUGIN)
    add_subdirectory(QtWidgetExPlugin)
endif ()

option(WIDGETEX_BUILD_TEST "enable qtwidgetex test project" OFF)

if (WIDGETEX_BUILD_TEST)
    add_subdirectory(test)
endif ()
