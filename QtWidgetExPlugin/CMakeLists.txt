cmake_minimum_required(VERSION 3.2)
project(QtWidgetExPlugin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BUILD_TYPE Release)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

find_package(Qt5 COMPONENTS Core Gui Widgets)

add_library(${PROJECT_NAME} SHARED
    buttons/qcheckboxexplugin.cpp
    buttons/qpushbuttonexplugin.cpp
    buttons/qradiobuttonexplugin.cpp
    buttons/qtoolbuttonexplugin.cpp
    
    display/qlabelexplugin.cpp

    input/qcomboboxexplugin.cpp
    input/qlineeditexplugin.cpp

    formeditor.qrc
    qtwidgetexplugin.cpp
)

add_library(qtwidgetex::plugin ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets qtwidgetex::lib)

message("qt5 designer dir: ${Qt5_DIR}/../../../plugins/designer")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${Qt5_DIR}/../../../plugins/designer
)