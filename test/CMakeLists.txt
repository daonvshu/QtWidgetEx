cmake_minimum_required(VERSION 3.12)
project(QtWidgetExTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Gui Widgets)

add_definitions(-DCONFIG_NETWORK_IMG)

add_executable(${PROJECT_NAME} WIN32
    lifecycle/lifecycle/FragmentManager.cpp
    lifecycle/lifecycle/FragmentManager.h
    lifecycle/lifecycle/Impl.h
    lifecycle/lifecycle/LifeCycleWidget.h

    pages/buttons.ui
    pages/buttonspage.cpp
    pages/buttonspage_p.cpp
    pages/buttonspage.h
    pages/buttonspage_p.h

    pages/displaywidgets.ui
    pages/displaywidgetspage.cpp
    pages/displaywidgetspage_p.cpp
    pages/displaywidgetspage.h
    pages/displaywidgetspage_p.h

    pages/inputwidgets.ui
    pages/inputwidgetspage.cpp
    pages/inputwidgetspage_p.cpp
    pages/inputwidgetspage.h
    pages/inputwidgetspage_p.h

    asyncsettertest.cpp

    widgetextest.cpp
    widgetextest.qrc
    widgetextest.ui
    main.cpp
)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets qtwidgetex::lib)
