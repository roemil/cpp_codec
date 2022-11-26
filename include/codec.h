#ifndef CODEC_H
#define CODEC_H

#include <string>
#include <memory>
#include "IEncryptionStrategy.h"

class Codec
{
private:
    std::unique_ptr<IEncryptionStrategy> encStrat_;

public:
    Codec(std::unique_ptr<IEncryptionStrategy> encStrat) : encStrat_ {std::move(encStrat)} {};
    ~Codec() = default;

    std::string encode_string(const std::string& PlainText);
    std::string decode_string(const std::string& EncryptedString);
};

#endif