#ifndef CAESAR_H
#define CAESAR_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include "types.h"

class Caesar // of type IEncryptionStrategy
{
private:
    std::unordered_map<char, std::string> map_;

public:
    Caesar() = default; // TODO: Should be Num shifts as input
    ~Caesar() = default;

    std::string encode_string(const std::string& PlainText);
    std::string decode_string(const std::string& EncryptedString);
};

#endif