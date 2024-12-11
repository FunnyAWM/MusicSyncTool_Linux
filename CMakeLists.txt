cmake_minimum_required(VERSION 3.16)

project(MusicSyncTool VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/funnyawm/Qt/6.8.1/gcc_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
find_package(ZLIB)
find_package(TagLib 2.0.0 REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    AboutPage.cpp
    LoadingPage.cpp
    MusicSyncTool.cpp
    ShowDupe.cpp
    Settings.cpp
    CopyResult.cpp
    Settings.h
    AboutPage.h
    LoadingPage.h
    MusicSyncTool.h
    ShowDupe.h
    CopyResult.h
    AboutPage.ui
    LoadingPage.ui
    MusicSyncTool.ui
    Settings.ui
    ShowDupe.ui
    CopyResult.ui
    MusicSyncTool.qrc
    MusicSyncTool.rc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MusicSyncTool
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MusicSyncTool APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MusicSyncTool SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MusicSyncTool
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MusicSyncTool PRIVATE Qt6::Widgets Qt6::Sql)
target_link_libraries(MusicSyncTool PRIVATE TagLib::tag)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MusicSyncTool)
endif()
set_target_properties(MusicSyncTool PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MusicSyncTool
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MusicSyncTool)
endif()
