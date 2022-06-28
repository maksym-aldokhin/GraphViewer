cmake_minimum_required(VERSION 3.14)

project(qmlGraphic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick charts)

set(source
    test/main.cpp

    details/Graphic.cpp
    details/GraphicController.cpp
    details/ValueStorage.cpp

    uiModels/GraphicsModel.cpp

    ui/utility/ModelUtil.cpp
    ui/utility/Palette.cpp
)

set(header
    details/Graphic.h
    details/GraphicController.h
    details/ValueStorage.h

    uiModels/GraphicsModel.h

    ui/utility/ModelUtil.h
    ui/utility/Palette.h
)


set(ui
    ui/ui.qrc
)

add_executable(qmlGraphic
    ${source}
    ${ui}
)

target_link_libraries(qmlGraphic PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Charts
)
