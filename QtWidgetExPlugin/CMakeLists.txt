cmake_minimum_required(VERSION 3.12)
project(QtWidgetExPlugin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR}UiPlugin QUIET)

if (NOT TARGET Qt${QT_VERSION_MAJOR}::UiPlugin)
    message(STATUS "Qt${QT_VERSION_MAJOR} UiPlugin not found; skipping QtWidgetExPlugin")
    return()
endif ()

add_library(${PROJECT_NAME} SHARED
    buttons/qcheckboxexplugin.h
    buttons/qcheckboxexplugin.cpp
    buttons/qpushbuttonexplugin.h
    buttons/qpushbuttonexplugin.cpp
    buttons/qradiobuttonexplugin.h
    buttons/qradiobuttonexplugin.cpp
    buttons/qtoolbuttonexplugin.h
    buttons/qtoolbuttonexplugin.cpp
    
    display/qlabelexplugin.h
    display/qlabelexplugin.cpp
    display/qprogressbarexplugin.h
    display/qprogressbarexplugin.cpp
    
    input/qcomboboxexplugin.h
    input/qcomboboxexplugin.cpp
    input/qlineeditexplugin.h
    input/qlineeditexplugin.cpp

    formeditor.qrc
    qtwidgetexplugin.h
    qtwidgetexplugin.cpp
)

add_library(qtwidgetex::plugin ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::UiPlugin qtwidgetex)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(TARGET_OUTPUT_NAME "qwidgetexplugin_d")
else()
    set(TARGET_OUTPUT_NAME "qwidgetexplugin")
endif()
message("config output name: ${TARGET_OUTPUT_NAME}")

if (WIN32 AND NOT CMAKE_CROSSCOMPILING)
    set(QT_DESIGNER_DIR "${Qt${QT_VERSION_MAJOR}_DIR}/../../../plugins/designer")
    message("qt designer dir: ${QT_DESIGNER_DIR}")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> "${QT_DESIGNER_DIR}/${TARGET_OUTPUT_NAME}.dll"
        VERBATIM
    )
endif ()
