#include "FileReader.h"

#include <sstream>
#include <fstream>
#include <cstdint>
#include <vector>

std::string FileReader::readFile(const std::string &fileName)
{
    std::ifstream t(fileName, std::ios::out | std::ios::binary);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

std::vector<uint8_t> FileReader::readBinaryFile(const std::string &fileName)
{
    std::ifstream input(fileName, std::ios::out | std::ios::binary);

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    return buffer;
}


void FileReader::writeToFile(const std::string& data)
{
    std::ofstream myfile;
    // TODO: Need to write the actual bytes and not the string entirely.
    myfile.open ("../data/out.txt");
    myfile << data;
    myfile.close();
}

void FileReader::writeToFile(const std::vector<uint8_t>& data)
{
    std::ofstream output("../data/out.bin", std::ios::out | std::ios::binary);
    output.write(reinterpret_cast<const char*>(data.data()), data.size());
    output.close();
}
