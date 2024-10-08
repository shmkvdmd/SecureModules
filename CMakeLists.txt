cmake_minimum_required(VERSION 3.5)

project(SecureModules VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Sql REQUIRED)
find_package(SQLite::SQLite3)
find_package(Qt6 REQUIRED COMPONENTS Network)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        loginform.cpp
        loginform.h
        loginform.ui
        eventtracker.cpp
        eventtracker.h
        eventtracker.ui
        databasemanager.h
        user.cpp
        user.h
        usermanager.cpp
        usermanager.h
        includes.h
        admin.h
        admin.cpp
        admin.ui
        registration.cpp
        registration.h
        registration.ui
        centerWindow.cpp
        bantracker.cpp
        bantracker.h
        bantracker.ui
        chart.cpp
        chart.h
        chart.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SecureModules
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SecureModules APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SecureModules SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SecureModules
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SecureModules PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SecureModules PRIVATE Qt6::Sql)
target_link_libraries(SecureModules PRIVATE Qt6::Network)


set_target_properties(SecureModules PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SecureModules
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SecureModules)
endif()

if(SQLite3_FOUND)
    include_directories(${SQLITE_INCLUDE_DIRS})
    target_link_libraries(SecureModules, ${SQLITE3_LIBRARIES})
endif(SQLite3_FOUND)
