#ifndef CODEC_H
#define CODEC_H

#include <string>
#include "types.h"
#include "tree.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>

struct compare{
    bool operator() (node* l, node*r){
        return l->freq > r->freq;
    }
};

std::map<const char, int> count_occurences(const std::string& PlainText);

class Codec
{
private:
    EncryptionType enc_type_;
    std::unordered_map<char, std::string> map_;
    std::priority_queue<node*, std::vector<node*>, compare> min_heap_;
    node* huffman_tree_;

    void build_huffman_codes(node* root, std::string String);
    std::string encode_string_huffman(const std::string& PlainText);
    std::string decode_string_huffman(const std::string& CompressedString);
public:
    Codec(EncryptionType enc_type_);
    ~Codec();

    std::string encode_string(const std::string& PlainText);
    std::priority_queue<node*, std::vector<node*>, compare> build_min_heap(const std::string& PlainText);

    std::string decode_string(const std::string& EncryptedString);
};

#endif