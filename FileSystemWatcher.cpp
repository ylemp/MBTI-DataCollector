#include "FileSystemWatcher.h"

/**
 * FileSystemWatcher class watches a directory for changes in files
 * @param directory Directory for detection of new files
 */
FileSystemWatcher::FileSystemWatcher(fs::path directory) :  detectionFolder_(std::move(directory)) {

    if(!is_directory(detectionFolder_)){
        std::cerr  << "Provided Detection Folder " << detectionFolder_ << " is NOT a valid directory" << std::endl;
        throw std::invalid_argument("Detection Folder is NOT a directory");
    }

    for(auto &fileName : fs::recursive_directory_iterator(detectionFolder_)){
        if(fileName.is_regular_file() && isValidLz4(fileName.path().filename().string())) {
            std::cout << "\tFileSystemWatcher Adding File: " << fileName << std::endl;
            //add the fully justified path in case of duplicate file names in sub dirs
            existingFiles_[fileName.path().string()] = std::filesystem::last_write_time(fileName);
        }
    }
}

/**
 * Runs the FileSystemWatcher
 * @param triggerEvent Functor to handle the actions done on a file
 */
void FileSystemWatcher::start(const std::function<void(std::string, FileStatus)> &triggerEvent) {

    while(watching_){
        std::this_thread::sleep_for(sleep_);

        //deletions
        //look through the map
        //if a file in our map no longer exists in the filesystem
        //then it has been deleted
        //remove it from the map
        for(auto const& pair : existingFiles_){
            if (!std::filesystem::exists(pair.first)) {
                triggerEvent(pair.first, FileStatus::deleted);
                existingFiles_.erase(pair.first);
            }
        }


        //creations or modifications
        //look through file system
        //if the file exists in the filesystem and in our map, check if it has been modified
        //if the file doesn't exist in our map then it is new
        for(auto &fileName : std::filesystem::recursive_directory_iterator(detectionFolder_)) {

            //record last write time to compare
            auto lastWriteTime = std::filesystem::last_write_time(fileName);

            //we already have the file in our map
            //compare write times
            //or,
            //we don't have it in our map, and it's a regular file
            //so, it's new
            if(contains(fileName.path().string())){
                if(existingFiles_[fileName.path().string()] != lastWriteTime){
                    existingFiles_[fileName.path().string()] = std::filesystem::last_write_time(fileName);
                    triggerEvent(fileName.path().string(), FileStatus::updated);
                }
            }else{
                if(fileName.is_regular_file() && isValidLz4(fileName.path().filename().string())) {
                    existingFiles_[fileName.path().string()] = lastWriteTime;
                    triggerEvent(fileName.path().string(), FileStatus::created);
                }
            }

        }
    }
}

/**
 * Stops the FileSystemWatcher
 */
void FileSystemWatcher::stop() {
    watching_ = false;

}

/**
 * helper function to check if a key exists in the file system map
 * @param key
 * @return true if the key value pair exists
 */
bool FileSystemWatcher::contains(const std::string &key) {
    auto el = existingFiles_.find(key);
    return el != existingFiles_.end();
}

/**
 * Destructor, stops the FileSystemWatcher
 */
FileSystemWatcher::~FileSystemWatcher() {
    stop();
}

