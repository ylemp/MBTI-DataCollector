# CMakeList.txt : CMake project for DataCollector-Collector, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("DataCollector")

if(NOT DEFINED CLI11_DIR)
  set (CLI11_DIR "CLI11-main" CACHE STRING "CLI11 git repository")
endif()

include_directories(${CLI11_DIR}/include)
add_subdirectory(CLI11-main)
target_link_libraries(CLI11)

enable_testing()

set(HEADERS
        "DataCollector.h"
        "FileSystemWatcher.h"
        "FileValidator.h")

set(SOURCES
        "DataCollector.cpp"
        "FileSystemWatcher.cpp")


# Add source to this project's executable.
add_executable(DataCollector DataCollectorService.cpp ${SOURCES} ${HEADERS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DataCollector PROPERTY CXX_STANDARD 17)
endif()

install(TARGETS DataCollector DESTINATION bin)

add_library(DataCollector_lib STATIC ${SOURCES} ${HEADERS})

find_package(GTest REQUIRED)

add_subdirectory(Google_tests)
add_subdirectory(tests)
