cmake_minimum_required(VERSION 3.16)

project(CPUBenchmarkQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Concurrent Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Concurrent Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Concurrent Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CPUBenchmarkQT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        cpuidentification.h
        cpuidentification.cpp
        cpuidwindow.h cpuidwindow.cpp cpuidwindow.ui
        cacheinfo.h
        memTransfer.cpp
        memTransfer.h
        rcdmemtransfer.h rcdmemtransfer.cpp rcdmemtransfer.ui
        resdmemtransfer.h resdmemtransfer.cpp resdmemtransfer.ui
        memAccess.cpp
        memAccess.h
        rcdmemaccess.h rcdmemaccess.cpp rcdmemaccess.ui
        resdmemaccess.h resdmemaccess.cpp resdmemaccess.ui
        encrDecr.cpp
        encrDecr.h
        rcdencrdecr.h rcdencrdecr.cpp rcdencrdecr.ui
        resdencrdecr.h resdencrdecr.cpp resdencrdecr.ui
        mandelbrot.h
        mandelbrot.cpp
        rcdmandelbrot.h rcdmandelbrot.cpp rcdmandelbrot.ui
        resdmandelbrot.h resdmandelbrot.cpp resdmandelbrot.ui
        rcdpcgrader.h rcdpcgrader.cpp rcdpcgrader.ui
        pcGrader.cpp
        pcGrader.h
        resdpcgrader.h resdpcgrader.cpp resdpcgrader.ui
        mandelbrotwidget.cpp
        mandelbrotwidget.h
        chartFactory.cpp
        chartFactory.h
        progress.h








    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CPUBenchmarkQT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CPUBenchmarkQT SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CPUBenchmarkQT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CPUBenchmarkQT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CPUBenchmarkQT PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Charts
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CPUBenchmarkQT)
endif()
set_target_properties(CPUBenchmarkQT PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CPUBenchmarkQT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CPUBenchmarkQT)
endif()
