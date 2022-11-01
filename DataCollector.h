#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <regex>

#include "FileSystemWatcher.h"


namespace fs = std::filesystem;

class DataCollector{

public:
    DataCollector(fs::path  detectionFolder, fs::path  collectionFolder, fs::path  archiveFolder);
    ~DataCollector();
    void collect();

private:


    void archiveDirectory(const std::filesystem::path&, const std::filesystem::path&);
    static void copyDirectory(const std::filesystem::path&, std::filesystem::path, std::time_t&);
    static void tarDirectory(const std::filesystem::path&, std::filesystem::path, std::time_t&);

    fs::path detectionFolder_;
    fs::path collectionFolder_;
    fs::path archiveFolder_;

    FileSystemWatcher fileSystemWatcher_ = FileSystemWatcher(detectionFolder_);

};
