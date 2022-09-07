#ifndef CODEC_H
#define CODEC_H

#include <string>
#include "types.h"

class Codec
{
private:
    EncryptionType enc_type_;
    std::string encode_string_caesar3(std::string& String);
    std::string decode_string_caesar3(const std::string& EncodedString);

public:
    Codec(EncryptionType enc_type_);
    ~Codec();

    std::string encode_string(std::string& String);

    std::string decode_string(const std::string& EncryptedString);
};

#endif