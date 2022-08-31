#pragma once

#include <string>
#include "types.h"

class decoder
{
private:
    EncryptionType enc_type_;
public:
    decoder(EncryptionType EncType);
    ~decoder();

    std::string decode_string(const std::string& EncryptedString);
    std::string decode_string_caesar3(const std::string& EncodedString);
};

