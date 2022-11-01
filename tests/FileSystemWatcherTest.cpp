#include <gtest/gtest.h>
#include "../FileSystemWatcher.h"

using namespace std;

TEST(FileSystemWatcherTests, FileSystemWatcherTest){

    fs::path detectionFolder(R"(C:\Workspace\MBTI\DataCollector\Detection)");

    FileSystemWatcher fileSystemWatcher = FileSystemWatcher(detectionFolder);
    EXPECT_TRUE(true);
}


TEST(FileSystemWatcherTests, FileSystemWatcherTestStop){

    fs::path detectionFolder(R"(C:\Workspace\MBTI\DataCollector\Detection)");

    FileSystemWatcher fileSystemWatcher = FileSystemWatcher(detectionFolder);
    fileSystemWatcher.stop();
    EXPECT_TRUE(true);
}