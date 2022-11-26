#include "caesar.h"
#include <map>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <bitset>

std::string encode_string_caesar3(const std::string& PlainText){
    std::string EncodedString;
    for(int i = 0; i < PlainText.size(); ++i){
        EncodedString.push_back(PlainText[i]+3);
    }
    return EncodedString;
}

std::string decode_string_caesar3(const std::string& EncodedString){
    std::string DecodedString;
    for(int i = 0; i < EncodedString.size(); i++){
        DecodedString.push_back(EncodedString[i] - 3);
    }
    return DecodedString;
}

std::string Caesar::encode(const std::string& PlainText){
    std::string EncodedString;
    EncodedString = encode_string_caesar3(PlainText);
    return EncodedString;
}

std::string Caesar::decode(const std::string& EncodedString){
    std::string DecodedString;
    DecodedString = decode_string_caesar3(EncodedString);
    return DecodedString;
}
