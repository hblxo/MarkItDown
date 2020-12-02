cmake_minimum_required(VERSION 3.14)
project(MarkItDown)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(Qt5_DIR "~/Qt/5.15.1/clang_64/lib/cmake/Qt5")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(MarkItDown main.cpp MainWindow.cpp MarkdownHandler.cpp TextEdit.cpp MyRes.qrc)
target_link_libraries(MarkItDown Qt5::Core Qt5::Widgets)