
#include "include/encoder.h"
#include "include/decoder.h"
#include <iostream>

int main(){
    EncryptionType EncType = Caesar3;
    encoder encoder(EncType);

    std::string String = "This will be encoded";
    std::string EncodedString = encoder.encode_string(String);
    std::cout << "Encoded String: " << EncodedString << std::endl;

    decoder decoder(EncType);
    std::string DecodedString = decoder.decode_string(EncodedString);
    std::cout << "Decoded String: " << DecodedString << std::endl;

    return 0;
}