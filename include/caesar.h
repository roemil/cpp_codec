#ifndef CAESAR_H
#define CAESAR_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include "types.h"
#include "IEncryptionStrategy.h"

class Caesar : public IEncryptionStrategy
{
private:
    std::unordered_map<char, std::string> map_;
    int shift_;

public:
    Caesar(int shift = 3) : shift_ {shift} {};
    std::string encode(const std::string& PlainText) override;
    std::string decode(const std::string& EncryptedString) override;
};

#endif