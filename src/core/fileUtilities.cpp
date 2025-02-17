#include "fileUtilities.h"
#include <fstream>
#include <sstream>

std::string readFileIntoString(const std::string &filepath)
{
    std::ifstream fileStream(filepath);
    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    return stringStream.str();
}