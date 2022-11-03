#include "DataCollector.h"

#include <utility>


using namespace std;

namespace fs = filesystem;


/**
 * Service that collects system information upon reception of a trigger event
 * The trigger event is raised when existence of a file with a certain name in a specified directory is detected.
 *
 * @param detectionFolder Detection Folder to detect creation of a file
 * @param collectionFolder Collection folder recursively collects individual files, as well as whole directories and their contents
 * @param archiveFolder Folder to store the copied files and tar files
 */
DataCollector::DataCollector(fs::path  detectionFolder, fs::path  collectionFolder, fs::path  archiveFolder) :
                             detectionFolder_(std::move(detectionFolder)),
                             collectionFolder_(std::move(collectionFolder)),
                             archiveFolder_(std::move(archiveFolder)){

    if(!is_directory(detectionFolder_)){
        cerr  << "Provided Detection Folder " << detectionFolder_ << "is NOT a valid directory" << endl;
        throw invalid_argument("Detection Folder is NOT a directory");
    }

    if(!is_directory(collectionFolder_)){
        cerr  << "Provided Collection Folder " << collectionFolder_ << "is NOT a valid directory" << endl;
        throw invalid_argument("Collection Folder is NOT a directory");
    }

    if(!is_directory(archiveFolder_)){
        cout << "archiveFolder directory is being created" << endl;
        //not necessarily an error, we can make the archive folder
        fs::create_directories(archiveFolder_);
    }
}

/**
 * Collect function passes a lambda function to the FileSystemWatcher
 * Allows for customizable handling of file system events
 */
void DataCollector::collect() {
    //pass a lambda to the start function of File System Watcher
    fileSystemWatcher_.start([this] (const std::string& fileName, FileStatus status, std::time_t writeTime) -> void {
        switch (status) {
            case FileStatus::created:
                cout << "File " << fileName << " has been created in the File System" << endl;
                archiveDirectory(collectionFolder_, archiveFolder_, writeTime);
                break;
            case FileStatus::updated:
                cout << "File " << fileName << " has been updated in the File System" << endl;
                break;
            case FileStatus::deleted:
                cout << "File " << fileName << " has been deleted from the File System" << endl;
                break;
            default:
                cerr << "File Status Error" << endl;
        }
    });
}

/**
 * Calls functions to copy and tar the collectionFolder into the archiveFolder
 * Creates a unique timestamp that is shared between the tar file and backup folder
 * @param collectionFolder Input folder for data collection
 * @param archiveFolder Output folder for archival of files
 */
void DataCollector::archiveDirectory(const filesystem::path& collectionFolder, const filesystem::path& archiveFolder, const std::time_t& writeTime) {
    cout << "Archiving Directory" << endl;

    copyDirectory(collectionFolder, archiveFolder, writeTime);
    tarDirectory(collectionFolder, archiveFolder, writeTime);
}

/**
 * Copies the source dir to the destination dir under the backups directory with unique timestamps
 * @param source Input folder for data collection
 * @param destination Output folder for archival of files
 * @param timestamp Time of folder creation
 */
void DataCollector::copyDirectory(const filesystem::path& source, filesystem::path destination, const std::time_t& timestamp) {

    destination /= "backups";
    if(!exists(destination)){
        fs::create_directories(destination);
    }

    destination /= "backup_";
    destination += to_string(timestamp);

    try {
        fs::copy(source, destination, fs::copy_options::recursive);
    }catch (exception e ){
        cerr << e.what() << endl;
    }
}

/**
 * Tars the source dir to the destination dir under the tars directory with unique timestamps
 * @param source Input folder for data collection
 * @param destination Output folder for archival of files
 * @param timestamp Time of tar creation
 */
void DataCollector::tarDirectory(const filesystem::path& source, filesystem::path destination, const std::time_t& timestamp) {

    destination /= "tars";
    if(!exists(destination)){
        fs::create_directories(destination);
    }

    destination /= "archive_";

    std::stringstream ss;
    ss << "tar -czf " <<  destination << timestamp << ".tar.gz  " << source;

    std::string z = ss.str();
    system(z.c_str());
}

/**
 * Destructor, stops the FileSystemWatcher
 */
DataCollector::~DataCollector() {
    fileSystemWatcher_.stop();
}