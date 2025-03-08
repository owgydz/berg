cmake_minimum_required(VERSION 3.)
project(BergGUI)

find_package(Qt5 REQUIRED Widgets)

add_executable(BergGUI 
    guimain.cpp
    gui.cpp
    buildwindow.cpp
    projectmanager.cpp
    targetselector.cpp
    progressbar.cpp
    settings.cpp
    logwindow.cpp
)

# Link with Qt5 (if using Qt)
target_link_libraries(BergGUI Qt5::Widgets)

# Include directories for GUI code
include_directories(gui)


