#include "include/codec.h"

Codec::Codec(EncryptionType EncType)
{
    enc_type_ = EncType;
}

Codec::~Codec()
{
}

std::string Codec::encode_string(std::string& String){
    std::string EncodedString;
    switch (enc_type_){
        case Caesar3:
            EncodedString = encode_string_caesar3(String);
            break;
        default:
            return "";
    }
    return EncodedString;
    
}

std::string Codec::encode_string_caesar3(std::string& String){
    std::string EncodedString;
    for(int i = 0; i < String.size(); ++i){
        EncodedString.push_back(String[i]+3);
    }
    return EncodedString;
}

std::string Codec::decode_string(const std::string& EncodedString){
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

std::string Codec::decode_string_caesar3(const std::string& EncodedString){
    std::string DecodedString;
    for(int i = 0; i < EncodedString.size(); i++){
        DecodedString.push_back(EncodedString[i] - 3);
    }
    return DecodedString;
}
