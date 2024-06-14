cmake_minimum_required(VERSION 3.5)

project(SlidingPuzzle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SlidingPuzzle
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        board.h board.cpp
        tile.h tile.cpp
        classes.qmodel
        game_manager.h game_manager.cpp


        main_menu_scene.h main_menu_scene.cpp
        my_pixmap_button.h my_pixmap_button.cpp
        leadership_scene.h leadership_scene.cpp
        settings_scene.h settings_scene.cpp
        game_scene.h game_scene.cpp
        tile_graphics_item.h tile_graphics_item.cpp
        moveable_tile.h moveable_tile.cpp
        immoveable_tile.h immoveable_tile.cpp

        my_label.h my_label.cpp
        my_check_box.h my_check_box.cpp
        my_text_box.h my_text_box.cpp
        my_select_box.h my_select_box.cpp
        my_button.h my_button.cpp
        my_radio_box.h my_radio_box.cpp
        my_timer.h my_timer.cpp
        end_scene.h end_scene.cpp
        my_rounded_rect.h my_rounded_rect.cpp
        score_parser.h score_parser.cpp




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SlidingPuzzle APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SlidingPuzzle SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SlidingPuzzle
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SlidingPuzzle PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SlidingPuzzle)
endif()
set_target_properties(SlidingPuzzle PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SlidingPuzzle
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SlidingPuzzle)
endif()
