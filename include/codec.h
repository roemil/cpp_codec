#ifndef CODEC_H
#define CODEC_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include "types.h"
#include "node.h"

struct compare{
    bool operator() (Node::node* l, Node::node*r){
        return l->freq > r->freq;
    }
};
namespace Utility{
std::map<const char, int> count_occurences(const std::string& PlainText);
void print_huffman(Node::node* root, std::string String);
}
class Codec
{
private:
    EncryptionType enc_type_;
    std::unordered_map<char, std::string> map_;
    std::priority_queue<Node::node*, std::vector<Node::node*>, compare> min_heap_;
    Node::node* huffman_tree_;

    std::priority_queue<Node::node*, std::vector<Node::node*>, compare> build_min_heap(const std::string& PlainText);
    void build_huffman_codes(Node::node* root, std::string String);
    std::string map_char_to_code(const std::string& PlainText);
    std::string encode_string_huffman(const std::string& PlainText);
    std::string decode_string_huffman(const std::string& CompressedString);
public:
    Codec(EncryptionType enc_type_);
    ~Codec();

    std::string encode_string(const std::string& PlainText);
    void build_huffman_tree(const std::string& PlainText);

    std::string decode_string(const std::string& EncryptedString);
};

#endif