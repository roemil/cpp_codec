#pragma once

#include <string>

class FileReader
{
    public:
        std::string readFile(const std::string& fileName);
        void writeToFile(const std::string& data);
};