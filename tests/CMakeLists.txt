project(Test)

include(CTest)


set(SOURCES
        "ValidatorTest.cpp"
)

add_executable(DataCollectorTests ${SOURCES})

target_link_libraries(DataCollectorTests PUBLIC gtest_main)

add_test(
        NAME ValidatorTests
        COMMAND ValidatorTests
)


#set(test_SRCS ADD ALL TEST SOURCE FILES HERE)
#add_executable(runUnitTests gtest.cpp ${test_SRCS})
#target_link_libraries(runUnitTests gtest gmock core)