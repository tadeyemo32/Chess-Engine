cmake_minimum_required(VERSION 3.16)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/engine.cpp
    src/game.cpp
    src/grid.cpp
)

include_directories(include)

find_package(raylib 4.0 QUIET)
if(NOT raylib_FOUND)
    message(STATUS "Raylib not found, using manual linking")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} ${SOURCES})

if(raylib_FOUND)
    target_link_libraries(${PROJECT_NAME} raylib)
else()
    if(APPLE)
        target_link_libraries(${PROJECT_NAME} "-framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL -lpthread -ldl -lm")
    else()
        target_link_libraries(${PROJECT_NAME} raylib m pthread dl GL X11)
    endif()
endif()

