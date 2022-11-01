#include <gtest/gtest.h>
#include "../DataCollector.h"
#include <thread>

using namespace std;

TEST(DataCollectorTests, DataCollectorTest){

    fs::path detectionFolder(R"(C:\Workspace\MBTI\DataCollector\Detection)");
    fs::path collectionFolder(R"(C:\Workspace\MBTI\DataCollector\Collection)");
    fs::path archiveFolder(R"(C:\Workspace\MBTI\DataCollector\Archive)");


    DataCollector dataCollector = DataCollector(detectionFolder, collectionFolder, archiveFolder);
    EXPECT_TRUE(true);
}
