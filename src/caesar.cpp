#include "caesar.h"

#include <string>

std::string Caesar::encode(const std::string& plainText){
    std::string encodedBytes;
    encodedBytes.reserve(plainText.size()/2);
    for(const auto& ch : plainText)
    {
        encodedBytes.push_back(ch + shift_);
    }
    return encodedBytes;
}

std::string Caesar::decode(const std::string& encodedString){
    std::string decodedString;
    decodedString.reserve(encodedString.size());
    for(const auto& ch : encodedString)
    {
        decodedString.push_back(ch - shift_);
    }
    return decodedString;
}
