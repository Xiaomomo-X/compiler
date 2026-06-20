cmake_minimum_required(VERSION 3.10)

project(Code)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(UI_FILES
    mainWindow.ui
)
add_executable(Code
    main.cpp
    mainWindow.cpp
    mainWindow.h
    mainWindow.ui
    
    token.cpp
    token.h

    lexer.h
    lexer.cpp

    parse.h
    parse.cpp

    parse_RD.h
    parse_RD.cpp

    semantic.h
    semantic.cpp
    
    ${UI_FILES} 
)

target_link_libraries(Code
    Qt5::Widgets
)