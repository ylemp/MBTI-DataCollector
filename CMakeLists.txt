# CMakeList.txt : CMake project for DataCollector-Collector, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("DataCollector")

#add_subdirectory(Google_tests)
#add_subdirectory(tests)

# Add source to this project's executable.
add_executable (DataCollector "DataCollector.cpp" "DataCollector.h" FileSystemWatcher.h FileSystemWatcher.cpp FileValidator.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DataCollector PROPERTY CXX_STANDARD 17)
endif()

install(TARGETS DataCollector DESTINATION .)
