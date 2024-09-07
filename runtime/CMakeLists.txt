cmake_minimum_required(VERSION 3.27.5)

project(runtime
    VERSION 0.1.0
    LANGUAGES CXX
)

set(QT_NO_CREATE_VERSIONLESS_FUNCTIONS true)

find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED)

find_package(nlohmann_json REQUIRED)
find_package(fmt REQUIRED)

qt6_standard_project_setup()

qt6_add_qml_module(runtime
    URI runtime
    VERSION 1.0
    RESOURCE_PREFIX "/runtime"
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)
add_library(runtime::Runtime ALIAS runtime)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(runtime
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/qmlruntime/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/qt/include>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/qmlruntime/include/qmlruntime
        ${CMAKE_CURRENT_SOURCE_DIR}/qmlruntime/src

        ${CMAKE_CURRENT_SOURCE_DIR}/cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/qt/src
)

target_link_libraries(runtime
    PUBLIC
        nlohmann_json::nlohmann_json
        fmt::fmt

    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

target_sources(runtime
    PUBLIC
        qmlruntime/include/qmlruntime/QmlRuntime.h
        qt/include/BridgeSingleton.h

    PRIVATE
        qmlruntime/src/QmlRuntime.cpp
        qmlruntime/src/QmlRuntimeController.h
        qmlruntime/src/QmlRuntimeController.cpp

        qt/src/BridgeSingleton.cpp

        cpp/ObjectAbstract.h
        cpp/FactoryAbstract.h

        qt/src/Object.h
        qt/src/Object.cpp
)

add_subdirectory(qmlruntime/tests)