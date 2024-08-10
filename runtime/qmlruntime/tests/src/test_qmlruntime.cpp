// Test interface
#include "runtime/Runtime.h"

#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace fs = std::filesystem;

#if !defined(TEST_SOURCE_DIR)
#pragma message "TEST_SOURCE_DIR not defined, assuming build in source tree."
#define TEST_SOURCE_DIR "../"
#endif

TEST(RuntimeTest, TestQmlEngine)
{
    // Simulate app
    //
    const char* progName = "test_program_name";
    char* mutableProgName = new char[std::strlen(progName) + 1];
    std::strcpy(mutableProgName, progName);

    char* appArgv[] = {mutableProgName, nullptr};
    int appArgc = 1;

    bool messageReceived = false;

    // Start runtime
    RuntimePtr runtime;
    runtime = Runtime::init(appArgc, appArgv, [&runtime, &messageReceived](const char* data) {
        auto payload = json::parse(data);
        EXPECT_TRUE(payload.contains("ok"));
        EXPECT_EQ(payload["ok"], true);

        // Mark message received and quit runtime
        messageReceived = true;
        runtime->quit();
    });

    auto testPath = fs::path(TEST_SOURCE_DIR) / "src/test.qml";
    auto res = runtime->run(testPath);
    EXPECT_EQ(res, 0);
    EXPECT_EQ(messageReceived, true);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
