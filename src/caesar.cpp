#include "caesar.h"

ByteVector Caesar::encode(const ByteVector& plainText){
    ByteVector encodedBytes;
    encodedBytes.reserve(plainText.size()/2);
    for(const auto& byte : plainText)
    {
        encodedBytes.push_back(static_cast<std::byte>(static_cast<char>(byte) + shift_));
    }
    return encodedBytes;
}

ByteVector Caesar::decode(const ByteVector& encodedBytes){
    ByteVector decodedBytes;
    decodedBytes.reserve(encodedBytes.size());
    for(const auto& byte : encodedBytes)
    {
        decodedBytes.push_back(static_cast<std::byte>(static_cast<char>(byte) - shift_));
    }
    return decodedBytes;
}
