#include "caesar.h"

std::string Caesar::encode(const std::string& PlainText){
    std::string EncodedString;
    for(int i = 0; i < PlainText.size(); ++i){
        EncodedString.push_back(PlainText[i] + shift_);
    }
    return EncodedString;
}

std::string Caesar::decode(const std::string& EncodedString){
    std::string DecodedString;
    for(int i = 0; i < EncodedString.size(); i++){
        DecodedString.push_back(EncodedString[i] - shift_);
    }
    return DecodedString;
}
