#ifndef HUFFMANBYTES_H
#define HUFFMANBYTES_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <cstddef>
#include "node.h"
#include "IEncryptionStrategy.h"

using ByteVector = std::vector<std::byte>;

struct compareNodes{
    bool operator() (Node::node* l, Node::node*r){
        return l->freq > r->freq;
    }
};

class HuffmanBytes
{
private:
    std::unordered_map<std::byte, ByteVector> map_;
    std::priority_queue<Node::node*, std::vector<Node::node*>, compareNodes> min_heap_;
    Node::node* huffman_tree_; //todo make to unique

    std::priority_queue<Node::node*, std::vector<Node::node*>, compareNodes> build_min_heap(const ByteVector& PlainText);
    void build_huffman_codes(Node::node* root, ByteVector String);
    ByteVector mapCharToCode(const ByteVector& PlainText);
    ByteVector encode_string_huffman(const ByteVector& PlainText);
    ByteVector decode_string_huffman(const ByteVector& CompressedString);
public:
    ByteVector encode(const ByteVector& PlainText);
    ByteVector decode(const ByteVector& EncryptedString);

    // Utilities for testing
    std::map<std::byte, int> count_occurences(const ByteVector& PlainText);
    void build_huffman_tree(const ByteVector& PlainText);
    void print_huffman(Node::node* root, ByteVector String);
};

#endif