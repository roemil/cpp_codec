#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include "types.h"

class encoder
{
private:
    EncryptionType enc_type;
    std::string encode_string_caesar3(std::string& String);
public:
    encoder(EncryptionType EncType);
    ~encoder();

    std::string encode_string(std::string& String);
};

#endif