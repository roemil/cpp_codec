#include "codec.h"
#include <memory>

std::string Codec::encode_string(const std::string& plainText){
    std::string encodedString;
    encodedString = encStrat_->encode(plainText);
    return encodedString;
}

std::string Codec::decode_string(const std::string& encodedString){
    std::string decodedString;
    decodedString = encStrat_->decode(encodedString);
    return decodedString;
}
