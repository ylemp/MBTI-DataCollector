#ifndef DATACOLLECTOR_FILEVALIDATOR_H
#define DATACOLLECTOR_FILEVALIDATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <regex>

static bool isValidLz4(const std::string& fileName){
    //std::cout << "Checking File " << fileName << std::endl;

    std::regex re(R"(^core\..*\..*\.lz4$)");
    std::smatch matches;
    auto const match = std::regex_search(fileName, re);
    //std::cout << "Is there a match: " << match << std::endl;

    return match;
}

#endif //DATACOLLECTOR_FILEVALIDATOR_H