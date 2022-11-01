project(DataCollectorTests)

include(CTest)


set(SOURCES
        ValidatorTest.cpp
        FileSystemWatcherTest.cpp
        DataCollectorTest.cpp)

add_executable(DataCollectorTests ${SOURCES})

target_link_libraries(DataCollectorTests PUBLIC
        DataCollector_lib
        gtest_main)

add_test(
        NAME ValidatorTests
        COMMAND ValidatorTests)

add_test(
        NAME FileSystemWatcherTests
        COMMAND FileSystemWatcherTests)

add_test(
        NAME DataCollectorTests
        COMMAND DataCollectorTests)