#include "decoder.h"

decoder::decoder(EncryptionType EncType)
{
    enc_type_ = EncType;
}

decoder::~decoder()
{
}

std::string decoder::decode_string(const std::string& EncodedString){
    std::string DecodedString;
    switch (enc_type_)
    {
    case Caesar3:
        DecodedString = decode_string_caesar3(EncodedString);
        break;
    default:
        DecodedString = "";
        break;
    }
    return DecodedString;
}

std::string decoder::decode_string_caesar3(const std::string& EncodedString){
    std::string DecodedString;
    for(int i = 0; i < EncodedString.size(); i++){
        DecodedString.push_back(EncodedString[i] - 3);
    }
    return DecodedString;
}
