#include "DataCollector.h"

#include <utility>


using namespace std;

namespace fs = filesystem;



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
        std::filesystem::create_directories(archiveFolder_);
    }

    //collect();
}

void DataCollector::collect() {
    //pass a lambda to the start function of File System Watcher
    fileSystemWatcher_.start([this] (const std::string& fileName, FileStatus status) -> void {
        switch (status) {
            case FileStatus::created:
                cout << "File " << fileName << " has been created in the File System" << endl;
                archiveDirectory(collectionFolder_, archiveFolder_);
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

void DataCollector::archiveDirectory(const filesystem::path& collectionFolder, const filesystem::path& archiveFolder) {
    cout << "Archiving Directory" << endl;

    std::time_t timestamp = std::time(nullptr);

    copyDirectory(collectionFolder, archiveFolder, timestamp);
    tarDirectory(collectionFolder, archiveFolder, timestamp);
}


void DataCollector::copyDirectory(const filesystem::path& source, filesystem::path destination, std::time_t& timestamp) {

    destination /= "backups";
    if(!exists(destination)){
        std::filesystem::create_directories(destination);
    }

    destination /= "backup_";
    destination += to_string(timestamp);

    fs::copy(source, destination, fs::copy_options::recursive);
}

void DataCollector::tarDirectory(const filesystem::path& source, filesystem::path destination, std::time_t& timestamp) {

    destination /= "tars";
    if(!exists(destination)){
        std::filesystem::create_directories(destination);
    }

    destination /= "archive_";

    std::stringstream ss;
    ss << "tar -czf " <<  destination << timestamp << ".tar.gz  " << source;

    std::string z = ss.str();
    system(z.c_str());
}

DataCollector::~DataCollector() {
    fileSystemWatcher_.stop();
}




int main(int argc, char* argv[])
{
	cout << "The number of provided args is: " << argc << endl;

	if (argc != 4) {
        cout << "You have provided an incorrect number of arguments " << argc << endl;
        return 0;
	}

    cout << "arg[0]: " << argv[0] << endl;
    cout << "arg[1]: " << argv[1] << endl;
    cout << "arg[2]: " << argv[2] << endl;
    cout << "arg[3]: " << argv[3] << endl;

    fs::path detectionFolder(argv[1]);
    fs::path collectionFolder(argv[2]);
    fs::path archiveFolder(argv[3]);

    cout << detectionFolder << endl;
    cout << collectionFolder << endl;
    cout << archiveFolder << endl;

    try {
        DataCollector dc = DataCollector(detectionFolder, collectionFolder, archiveFolder);
        dc.collect();
    }catch (invalid_argument& e){
        cerr << e.what() << endl;
        return -1;
    }
    return 0;
}


