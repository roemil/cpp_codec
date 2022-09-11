#include "include/codec.h"
#include <map>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <bitset>

std::map<const char, int> count_occurences(const std::string& PlainText){
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

Codec::Codec(EncryptionType EncType)
{
    enc_type_ = EncType;
}

Codec::~Codec()
{
}

std::priority_queue<node*, std::vector<node*>, compare> Codec::build_min_heap(const std::string& PlainText){
    std::map<const char, int> occurences = count_occurences(PlainText);
    std::priority_queue<node*, std::vector<node*>, compare> minheap;
    Tree tree;
    for(auto iter = occurences.rbegin(); iter != occurences.rend(); ++iter){
        node* Node = tree.GetNewNode(iter->first, iter->second);
        minheap.push(Node);
    }
    return minheap;
}

void print_huffman(node* root, std::string String){
    if(!root) return;

    if(root->ch != '$'){
        std::cout << root->ch << ": " << String << std::endl;
    }
    print_huffman(root->left, String + "0");
    print_huffman(root->right, String + "1");
}

void Codec::build_huffman_codes(node* root, std::string String){
    if(!root) return;

    if(root->ch != '$'){
        map_.insert({root->ch, String});
    }
    build_huffman_codes(root->left, String + "0");
    build_huffman_codes(root->right, String + "1");
}

void traverse_tree(node* root){
    if(root == nullptr) return;
    std::cout << "ch: " << root->ch << std::endl;
    traverse_tree(root->left);
    traverse_tree(root->right);

}

std::string Codec::encode_string_huffman(const std::string& PlainText){
    std::priority_queue<node*, std::vector<node*>, compare> minheap = build_min_heap(PlainText);
    Tree BTree;
    while(minheap.size() != 1){
        node* Left = minheap.top();
        minheap.pop();
        node* Right = minheap.top();
        minheap.pop();
        node* NewNode = BTree.GetNewNode('$', Left->freq+Right->freq); // TODO: Create a node file separate from tree
        NewNode->left = Left;
        NewNode->right = Right;
        minheap.push(NewNode);
    }

    build_huffman_codes(minheap.top(), "");
    min_heap_ = minheap;
    huffman_tree_ = minheap.top();

    std::string result;
    for(const char& ch: PlainText){
        auto code = map_.find(ch);
        result += code->second;
    }

    return result; // TODO: Rename to result_
}

std::string encode_string_caesar3(const std::string& PlainText){
    std::string EncodedString;
    for(int i = 0; i < PlainText.size(); ++i){
        EncodedString.push_back(PlainText[i]+3);
    }
    return EncodedString;
}

std::string Codec::encode_string(const std::string& PlainText){
    std::string EncodedString;
    switch (enc_type_){
        case Caesar3:
            EncodedString = encode_string_caesar3(PlainText);
            break;
        case Huffman:
            EncodedString = encode_string_huffman(PlainText);
            break;
        default:
            return "";
    }
    return EncodedString;
}

std::string Codec::decode_string_huffman(const std::string& CompressedString){
    node* Head = huffman_tree_;
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

std::string decode_string_caesar3(const std::string& EncodedString){
    std::string DecodedString;
    for(int i = 0; i < EncodedString.size(); i++){
        DecodedString.push_back(EncodedString[i] - 3);
    }
    return DecodedString;
}

std::string Codec::decode_string(const std::string& EncodedString){
    std::string DecodedString;
    switch (enc_type_)
    {
    case Caesar3:
        DecodedString = decode_string_caesar3(EncodedString);
        break;
    case Huffman:
        DecodedString = decode_string_huffman(EncodedString);
        break;
    default:
        DecodedString = "";
        break;
    }
    return DecodedString;
}
