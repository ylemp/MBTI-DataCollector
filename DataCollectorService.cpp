#include "DataCollector.h"

using namespace std;

namespace fs = filesystem;

/**
 * Entry point for the application
 * @param argc Argument count
 * @param argv Argument list
 * @return int
 */
int main(int argc, char* argv[])
{
    cout << "The number of provided args is: " << argc << endl;

    if (argc != 4) {
        cout << "You have provided an incorrect number of arguments " << argc << endl;
        return -1;
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