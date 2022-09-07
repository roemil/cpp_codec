#ifndef CODEC_H
#define CODEC_H

#include <string>
#include "types.h"
#include <map>

class Codec
{
    typedef struct {
        char letter;
        int freq;
        struct Node* left;
        struct Node* right;
    } Node;

private:
    EncryptionType enc_type_;

public:
    Codec(EncryptionType enc_type_);
    ~Codec();

    std::string encode_string(const std::string& PlainText);
    ByteVector compress_string(const std::string& PlainText);
    std::map<const char, int> count_occurences(const std::string& PlainText);

    std::string decode_string(const std::string& EncryptedString);
};

#endif