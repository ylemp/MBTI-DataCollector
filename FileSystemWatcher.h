#ifndef DATACOLLECTOR_FILESYSTEMWATCHER_H
#define DATACOLLECTOR_FILESYSTEMWATCHER_H


#include <filesystem>
#include <iostream>
#include <thread>
#include "FileValidator.h"

namespace fs = std::filesystem;

enum class FileStatus {created, updated, deleted};

class FileSystemWatcher {

public:

    explicit FileSystemWatcher(fs::path directory);
    ~FileSystemWatcher();
    void start(const std::function<void (std::string, FileStatus)> &triggerEvent);
    void stop();

private:

    fs::path detectionFolder_;
    std::unordered_map<std::string, std::filesystem::file_time_type> existingFiles_;
    bool watching_ = true;
    std::chrono::duration<int, std::milli> sleep_ = std::chrono::milliseconds(5000);

    bool contains(const std::string&);

};

#endif //DATACOLLECTOR_FILESYSTEMWATCHER_H