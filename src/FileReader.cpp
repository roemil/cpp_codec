#include "FileReader.h"

#include <sstream>
#include <fstream>

std::string FileReader::readFile(const std::string &fileName)
{
    std::ifstream t(fileName);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void FileReader::writeToFile(const std::string& data)
{
    std::ofstream myfile;
    // TODO: Need to write the actual bytes and not the string entirely.
    myfile.open ("../data/out.txt");
    myfile << data;
    myfile.close();
}
