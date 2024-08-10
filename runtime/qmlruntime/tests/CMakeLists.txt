cmake_minimum_required(VERSION 3.27.5)

project(test_qmlruntime
    VERSION 0.1.0
    LANGUAGES CXX
)

# Create the executable target
add_executable(test_qmlruntime
    src/test_qmlruntime.cpp
)

target_compile_definitions(test_qmlruntime PRIVATE TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_options(test_qmlruntime PRIVATE -Wall -Wextra)

# Link qmlruntime and Qt libraries
target_link_libraries(test_qmlruntime PRIVATE qmlruntime)

# Specify the installation directory
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Enable testing
enable_testing()

# Find the GoogleTest package
find_package(GTest REQUIRED)

# Include GoogleTest
include(GoogleTest)

# Link GoogleTest libraries
target_link_libraries(test_qmlruntime PRIVATE GTest::GTest GTest::Main)

# Add the tests
gtest_discover_tests(test_qmlruntime)
