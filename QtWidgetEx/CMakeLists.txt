cmake_minimum_required(VERSION 3.2)
project(qtwidgetex)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets)

if(CONFIG_NETWORK_IMG)
message("config network image!")
file(GLOB NET_IMG src/utils/networkimagegetter.cpp include/utils/networkimagegetter.h)
find_package(Qt5Network)
add_definitions(-DCONFIG_NETWORK_IMG)
endif()

add_library(${PROJECT_NAME}
    src/buttons/qcheckboxex.cpp
    src/buttons/qpushbuttonex.cpp
    src/buttons/qradiobuttonex.cpp
    src/buttons/qtoolbuttonex.cpp
    
    src/display/qlabelex.cpp
    src/display/qprogressbarex.cpp

    src/input/qcomboboxex.cpp
    src/input/qlineeditex.cpp

    src/eventex/mouseeventex.cpp

    src/interface/asyncdatasetter.cpp
    src/interface/gifsetterinterface.cpp
    src/interface/iconsetterinterface.cpp
    src/interface/imagesetterinterface.cpp
    src/interface/listelementsetter.cpp
    src/interface/textsetterinterface.cpp

    src/utils/buttongrouputil.cpp
    src/utils/regexpwidget.cpp

    include/exglobal.h
    include/qabstractbuttonex.h
    include/qcheckboxex.h
    include/qcomboboxex.h
    include/qlabelex.h
    include/qlineeditex.h
    include/qpushbuttonex.h
    include/qradiobuttonex.h
    include/qtoolbuttonex.h
    include/qprogressbarex.h

    include/eventex/mouseeventex.h
    include/eventex/simpleeventex.h

    include/interface/asyncdatasetter.h
    include/interface/gifsetterinterface.h
    include/interface/iconsetterinterface.h
    include/interface/imagesetterinterface.h
    include/interface/listelementsetter.h
    include/interface/simpledatasetter.h
    include/interface/textsetterinterface.h

    include/utils/buttongrouputil.h
    include/utils/regexpwidget.h
    
    ${NET_IMG}
)

target_include_directories(${PROJECT_NAME} PUBLIC include/)

add_library(qtwidgetex::lib ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)

if(CONFIG_NETWORK_IMG)
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Network)
endif()