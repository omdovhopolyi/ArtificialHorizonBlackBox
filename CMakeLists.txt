cmake_minimum_required(VERSION 3.5)

project(ArtificialHorizonBlackBox VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ArtificialHorizonBlackBox
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/maincontroller.h src/maincontroller.cpp
        src/savemanager.h src/savemanager.cpp
        src/datapoint.h

        src/dataprovider.h
        src/uartdatareceiver.h src/uartdatareceiver.cpp
        src/appconfig.h src/appconfig.cpp
        src/workers/dataworker.h src/workers/dataworker.cpp
        src/workers/uartdataworker.h src/workers/uartdataworker.cpp
        src/workers/testdataworker.h src/workers/testdataworker.cpp
        src/testdatareceiver.h src/testdatareceiver.cpp
        resources.qrc
        src/Modes/basemode.h src/Modes/basemode.cpp
        src/Modes/uartmode.h src/Modes/uartmode.cpp
        src/Modes/runmode.h src/Modes/runmode.cpp
        src/Modes/testmode.h src/Modes/testmode.cpp
        src/workers/saveworker.h src/workers/saveworker.cpp
        src/workers/runworker.h src/workers/runworker.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ArtificialHorizonBlackBox APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ArtificialHorizonBlackBox SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ArtificialHorizonBlackBox
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ArtificialHorizonBlackBox PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ArtificialHorizonBlackBox)
endif()
set_target_properties(ArtificialHorizonBlackBox PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ArtificialHorizonBlackBox
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ArtificialHorizonBlackBox)
endif()
