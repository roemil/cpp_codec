#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <cstddef>
#include "node.h"
#include "IEncryptionStrategy.h"


struct compareNodes{
    bool operator() (Node::node* l, Node::node*r){
        return l->freq > r->freq;
    }
};

class Huffman : public IEncryptionStrategy
{
private:
    std::unordered_map<char, std::string> map_;
    std::priority_queue<Node::node*, std::vector<Node::node*>, compareNodes> min_heap_;
    Node::node* huffman_tree_; //todo make to unique

    std::priority_queue<Node::node*, std::vector<Node::node*>, compareNodes> build_min_heap(const std::string& PlainText);
    void build_huffman_codes(Node::node* root, std::string String);
    std::string mapCharToCode(const std::string& PlainText);
public:
    std::string encode(const std::string& PlainText);
    std::string decode(const std::string& EncryptedString);

    // Utilities for testing
    std::map<char, int> count_occurences(const std::string& PlainText);
    void build_huffman_tree(const std::string& PlainText);
    void print_huffman(Node::node* root, std::string String);
};

#endif