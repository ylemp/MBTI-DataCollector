#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <regex>
#include <chrono>
#include <ctime>

#include "FileSystemWatcher.h"


namespace fs = std::filesystem;

class DataCollector{

public:
    DataCollector(fs::path  detectionFolder, fs::path  collectionFolder, fs::path  archiveFolder);
    ~DataCollector();
    void collect();

private:


    void archiveDirectory(const fs::path&, const fs::path&, const std::time_t&);
    void copyDirectory(const fs::path&, fs::path, const std::time_t&);
    void tarDirectory(const fs::path&, fs::path, const std::time_t&);

    fs::path detectionFolder_;
    fs::path collectionFolder_;
    fs::path archiveFolder_;

    FileSystemWatcher fileSystemWatcher_ = FileSystemWatcher(detectionFolder_);

};
