#include "encoder.h"

encoder::encoder(EncryptionType EncType)
{
    enc_type = EncType;
}

encoder::~encoder()
{
}

std::string encoder::encode_string(std::string& String){
    std::string EncodedString;
    switch (enc_type){
        case Caesar3:
            EncodedString = encode_string_caesar3(String);
            break;
        default:
            return "";
    }
    return EncodedString;
    
}

std::string encoder::encode_string_caesar3(std::string& String){
    std::string EncodedString;
    for(int i = 0; i < String.size(); ++i){
        EncodedString.push_back(String[i]+3);
    }
    return EncodedString;
}