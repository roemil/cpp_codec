#include "Huffman.h"
#include <map>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <string>

std::map<char, int> Huffman::count_occurences(const std::string& plainText){
    std::map<char, int> occurences;
    for(const auto& byte : plainText){
        occurences[byte] += 1;
    }
    return occurences;
}

void Huffman::print_huffman(Node::node* root, std::string String){
    if(!root) return;

    if(root->ch != '$'){
        std::cout << +root->ch << ": ";
        for(const auto& b : String)
        {
            std::cout << static_cast<char>(b) << " ";  
        } 
        std::cout << std::endl;
    }
    auto left = String;
    auto right = String;
    left.push_back('0');
    right.push_back('1');
    print_huffman(root->left, left);
    print_huffman(root->right, right);
}

std::priority_queue<Node::node*, std::vector<Node::node*>, compareNodes> Huffman::build_min_heap(const std::string& PlainText){
    const auto occurences = count_occurences(PlainText);
    std::priority_queue<Node::node*, std::vector<Node::node*>, compareNodes> minheap;
    for(auto iter = occurences.begin(); iter != occurences.end(); ++iter){
        Node::node* Node = Node::CreateNewNode(static_cast<char>(iter->first), iter->second);
        minheap.push(Node);
    }

    return minheap;
}

void Huffman::build_huffman_tree(const std::string& PlainText){
    auto minheap = build_min_heap(PlainText);
    while(minheap.size() != 1){
        Node::node* Left = minheap.top();
        minheap.pop();
        Node::node* Right = minheap.top();
        minheap.pop();
        Node::node* NewNode = Node::CreateNewNode('$', Left->freq+Right->freq);
        NewNode->left = Left;
        NewNode->right = Right;
        minheap.push(NewNode);
    }
    huffman_tree_ = minheap.top();
}

void Huffman::build_huffman_codes(Node::node* root, std::string String){
    if(!root) return;

    if(root->ch != '$'){
        map_.insert({root->ch, String});
    }
    auto left = String;
    auto right = String;
    left.push_back('0');
    right.push_back('1');
    build_huffman_codes(root->left, left);
    build_huffman_codes(root->right, right);
}

std::string Huffman::mapCharToCode(const std::string& plainText){
    std::string result;
    result.reserve(plainText.size());
    for(const auto& byte: plainText){
        auto code = map_.find(byte);
        for(const auto& codedByte : code->second)
        {
            result.push_back(codedByte);
        }
    }

    return result;
}

// TODO: Use template for string and bits?
std::string Huffman::encode(const std::string& PlainText){
    build_huffman_tree(PlainText);
    build_huffman_codes(huffman_tree_, {});

    return mapCharToCode(PlainText);
}

std::string Huffman::decode(const std::string& EncodedString){
    Node::node* Head = huffman_tree_;
    std::string result;
    for(const auto& ch : EncodedString){
        if(ch == '0'){
            Head = Head->left;
        }else{
            Head = Head->right;
        }
        if(Head->left == nullptr && Head->right == nullptr){
            result.push_back(Head->ch);
            Head = huffman_tree_;
        }
    }
    return result;
}
