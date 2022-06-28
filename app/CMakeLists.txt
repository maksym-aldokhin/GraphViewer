cmake_minimum_required(VERSION 3.14)

project(GraphViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(GRAPH_VIEWER_TEST_MODE)
set(GRAPH_VIEWER_TEST_MODE OFF CACHE BOOL "GRAPH_VIEWER_TEST_MODE")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick charts)

set(source
    public/Graphics.cpp

    details/Graphic.cpp
    details/GraphicController.cpp
    details/ValueStorage.cpp

    uiModels/GraphicsModel.cpp

    ui/utility/ModelUtil.cpp
    ui/utility/Palette.cpp
)

if ( GRAPH_VIEWER_TEST_MODE )
    message(STATUS "GraphViewer set main.cpp")
    list(APPEND source
        test/main.cpp
    )
endif()

set(header
    public/Graphics.h

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

if ( GRAPH_VIEWER_TEST_MODE )
    message(STATUS "GraphViewer generate .exe")
    add_executable(GraphViewer
        ${source}
        ${header}
        ${ui}
    )
else()
    message(STATUS "GraphViewer generate .dll")
    add_library ( GraphViewer SHARED
        ${source}
        ${header}
        ${ui}
    )

    add_compile_definitions(GraphViewer_LIBRARY)
endif()

target_link_libraries(GraphViewer PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Charts
)
