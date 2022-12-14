#include "DataCollector.h"
#include "CLI11.hpp"

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
    CLI::App app{"App description"};

    std::string flagFilenameD;
    app.add_option("-d,--detect", flagFilenameD, "The Detection folder")->required(true);

    std::string flagFilenameC;
    app.add_option("-c,--collect", flagFilenameC, "The Collection folder")->required(true);

    std::string flagFilenameA;
    app.add_option("-a,--archive", flagFilenameA, "The Archive folder")->required(true);

    try{
        CLI11_PARSE(app, argc, argv);

        fs::path detectionFolder(flagFilenameD);
        fs::path collectionFolder(flagFilenameC);
        fs::path archiveFolder(flagFilenameA);

        DataCollector dc = DataCollector(detectionFolder, collectionFolder, archiveFolder);
        dc.collect();

    }catch (CLI::ParseError e){
        app.exit(e);
    }catch (invalid_argument& e){
        cerr << e.what() << endl;
        return -1;
    }

    return 0;
}