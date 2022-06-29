cmake_minimum_required(VERSION 3.5)

project(DDL-Firewall VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        frontend/main.cpp
        frontend/mainwindow.cpp
        frontend/mainwindow.h
        frontend/mainwindow.ui
        backend/3rdparty/jsoncpp/jsoncpp.cpp
        backend/classes/reminder.cpp
        backend/classes/task.cpp
        backend/classes/subtask.cpp
        backend/classes/tasklist.cpp
        backend/config/config.cpp
        backend/data/data.cpp
        backend/data/json_io.cpp
        backend/fileio/textfile.cpp
        backend/self_test/data_gen.cpp
        frontend/add_job.cpp
        frontend/add_sche_task.cpp
        frontend/add_tasklist.cpp
        frontend/add_subtask.cpp
        frontend/add_reminder.cpp
        frontend/calendar_type.cpp
        frontend/errors.cpp
        frontend/edit_job.cpp
        frontend/edit_sche_task.cpp
        frontend/edit_subtask.cpp
        frontend/edit_reminder.cpp
        frontend/ddlfirewall.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DDL-Firewall
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DDL-Firewall APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DDL-Firewall SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DDL-Firewall
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DDL-Firewall PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(DDL-Firewall PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DDL-Firewall)
endif()
