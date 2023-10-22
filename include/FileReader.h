#pragma once

#include <string>
#include <vector>

class FileReader
{
    public:
        // TODO: API should be same, ie string in, string out
        // bin vector in, bin vector out.
        std::string readFile(const std::string &fileName);
        std::vector<uint8_t> readBinaryFile(const std::string& fileName);
        void writeToFile(const std::string& data);
        void writeToFile(const std::vector<uint8_t>& data);
};