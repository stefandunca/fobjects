cmake_minimum_required(VERSION 3.27.5)

project(qmlruntime
    VERSION 0.1.0
    LANGUAGES CXX
)

set(QT_NO_CREATE_VERSIONLESS_FUNCTIONS true)

find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED)

find_package(nlohmann_json REQUIRED)
find_package(fmt REQUIRED)

qt6_standard_project_setup()

qt6_add_qml_module(qmlruntime
    URI qmlruntime
    VERSION 1.0
)
add_library(qmlruntime::Runtime ALIAS qmlruntime)

set(CMAKE_CXX_STANDARD 21)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(qmlruntime
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/runtime
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(qmlruntime
    PUBLIC
        nlohmann_json::nlohmann_json
        fmt::fmt

    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

target_sources(qmlruntime
    PUBLIC
        include/runtime/Runtime.h

    PRIVATE
        src/Runtime.cpp
        src/RuntimeController.h
        src/RuntimeController.cpp
)

add_subdirectory(tests)