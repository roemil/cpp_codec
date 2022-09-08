#ifndef CODEC_H
#define CODEC_H

#include <string>
#include "types.h"
#include "tree.h"
#include <map>

class Codec
{
private:
    EncryptionType enc_type_;
    std::string result;

public:
    Codec(EncryptionType enc_type_);
    ~Codec();

    std::string encode_string(const std::string& PlainText);
    std::vector<node*> compress_string(const std::string& PlainText);
    std::map<const char, int> count_occurences(const std::string& PlainText);
    Tree build_min_heap(const std::string& PlainText);

    std::string decode_string(const std::string& EncryptedString);
};

#endif