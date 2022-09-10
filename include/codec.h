#ifndef CODEC_H
#define CODEC_H

#include <string>
#include "types.h"
#include "tree.h"
#include <unordered_map>
#include <map>

class Codec
{
private:
    EncryptionType enc_type_;
    std::string result;
    std::unordered_map<char, std::string> map_;
    void build_huffman_codes(node* root, std::string String);

public:
    Codec(EncryptionType enc_type_);
    ~Codec();

    std::string encode_string(const std::string& PlainText);
    std::string compress_string(const std::string& PlainText);
    std::map<const char, int> count_occurences(const std::string& PlainText);
    Tree build_min_heap(const std::string& PlainText);

    std::string decode_string(const std::string& EncryptedString);
};

#endif