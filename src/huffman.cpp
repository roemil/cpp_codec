#include "huffman.h"
#include <map>
#include <unordered_map>
#include <iostream>
#include <queue>

std::map<const char, int> Huffman::count_occurences(const std::string& PlainText){
    std::map<const char, int> occurences;
    for(const char& Char : PlainText){
        if(occurences.find(Char) == occurences.end()){
            occurences.insert({Char, 1});
        }else{
            auto OldValue = occurences.find(Char);
            occurences.insert({Char, OldValue->second++});
        }
    }
    return occurences;
}

void Huffman::print_huffman(Node::node* root, std::string String){
    if(!root) return;

    if(root->ch != '$'){
        std::cout << root->ch << ": " << String << std::endl;
    }
    print_huffman(root->left, String + "0");
    print_huffman(root->right, String + "1");
}

std::priority_queue<Node::node*, std::vector<Node::node*>, compare> Huffman::build_min_heap(const std::string& PlainText){
    std::map<const char, int> occurences = count_occurences(PlainText);
    std::priority_queue<Node::node*, std::vector<Node::node*>, compare> minheap;
    for(auto iter = occurences.begin(); iter != occurences.end(); ++iter){
        Node::node* Node = Node::CreateNewNode(iter->first, iter->second);
        minheap.push(Node);
    }

    return minheap;
}

void Huffman::build_huffman_tree(const std::string& PlainText){
    std::priority_queue<Node::node*, std::vector<Node::node*>, compare> minheap = build_min_heap(PlainText);
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

void Huffman::build_huffman_codes(Node::node* root, const std::string& String){
    if(!root) return;

    if(root->ch != '$'){
        map_.insert({root->ch, String});
    }
    build_huffman_codes(root->left, String + "0");
    build_huffman_codes(root->right, String + "1");
}

std::string Huffman::map_char_to_code(const std::string& plainText){
    std::string result;
    result.reserve(plainText.size());
    for(const char& ch: plainText){
        auto code = map_.find(ch);
        result += code->second;
    }

    return result;
}

std::string Huffman::encode_string_huffman(const std::string& PlainText){
    build_huffman_tree(PlainText);
    build_huffman_codes(huffman_tree_, "");

    return map_char_to_code(PlainText);
}

std::string Huffman::decode_string_huffman(const std::string& CompressedString){
    Node::node* Head = huffman_tree_;
    std::string result;
    for(const char& ch : CompressedString){
        if(ch == '0'){
            Head = Head->left;
        }else{
            Head = Head->right;
        }
        if(Head->left == nullptr && Head->right == nullptr){
            result += Head->ch;
            Head = huffman_tree_;
        }
    }
    return result;

}
// TODO: Use template for string and bits?
std::string Huffman::encode(const std::string& PlainText){
    return encode_string_huffman(PlainText);
}

std::string Huffman::decode(const std::string& EncodedString){
    return decode_string_huffman(EncodedString);
}
