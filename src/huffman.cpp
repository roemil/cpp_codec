#include "Huffman.h"
#include <map>
#include <unordered_map>
#include <iostream>
#include <queue>

std::map<std::byte, int> Huffman::count_occurences(const ByteVector& plainText){
    std::map<std::byte, int> occurences;
    for(const auto& byte : plainText){
        occurences[byte] += 1;
    }
    return occurences;
}

void Huffman::print_huffman(Node::node* root, ByteVector String){
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
    left.push_back(static_cast<std::byte>('0'));
    right.push_back(static_cast<std::byte>('1'));
    print_huffman(root->left, left);
    print_huffman(root->right, right);
}

std::priority_queue<Node::node*, std::vector<Node::node*>, compareNodes> Huffman::build_min_heap(const ByteVector& PlainText){
    std::map<std::byte, int> occurences = count_occurences(PlainText);
    std::priority_queue<Node::node*, std::vector<Node::node*>, compareNodes> minheap;
    for(auto iter = occurences.begin(); iter != occurences.end(); ++iter){
        Node::node* Node = Node::CreateNewNode(static_cast<char>(iter->first), iter->second);
        minheap.push(Node);
    }

    return minheap;
}

void Huffman::build_huffman_tree(const ByteVector& PlainText){
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

void Huffman::build_huffman_codes(Node::node* root, ByteVector String){
    if(!root) return;

    if(root->ch != '$'){
        map_.insert({static_cast<std::byte>(root->ch), String});
    }
    auto left = String;
    auto right = String;
    left.push_back(static_cast<std::byte>('0'));
    right.push_back(static_cast<std::byte>('1'));
    build_huffman_codes(root->left, left);
    build_huffman_codes(root->right, right);
}

ByteVector Huffman::mapCharToCode(const ByteVector& plainText){
    ByteVector result;
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

ByteVector Huffman::encode_string_huffman(const ByteVector& PlainText){
    build_huffman_tree(PlainText);
    build_huffman_codes(huffman_tree_, {});

    return mapCharToCode(PlainText);
}

ByteVector Huffman::decode_string_huffman(const ByteVector& CompressedString){
    Node::node* Head = huffman_tree_;
    ByteVector result;
    for(const auto& ch : CompressedString){
        if(static_cast<char>(ch) == '0'){
            Head = Head->left;
        }else{
            Head = Head->right;
        }
        if(Head->left == nullptr && Head->right == nullptr){
            result.push_back(static_cast<std::byte>(Head->ch));
            Head = huffman_tree_;
        }
    }
    return result;

}
// TODO: Use template for string and bits?
ByteVector Huffman::encode(const ByteVector& PlainText){
    return encode_string_huffman(PlainText);
}

ByteVector Huffman::decode(const ByteVector& EncodedString){
    return decode_string_huffman(EncodedString);
}
