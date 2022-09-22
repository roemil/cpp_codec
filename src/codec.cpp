#include "codec.h"
#include <map>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <bitset>


std::map<const char, int> Utility::count_occurences(const std::string& PlainText){
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

void Utility::print_huffman(Node::node* root, std::string String){
    if(!root) return;

    if(root->ch != '$'){
        std::cout << root->ch << ": " << String << std::endl;
    }
    print_huffman(root->left, String + "0");
    print_huffman(root->right, String + "1");
}


Codec::Codec(EncryptionType EncType)
{
    enc_type_ = EncType;
}

Codec::~Codec()
{
}

std::priority_queue<Node::node*, std::vector<Node::node*>, compare> Codec::build_min_heap(const std::string& PlainText){
    std::map<const char, int> occurences = Utility::count_occurences(PlainText);
    std::priority_queue<Node::node*, std::vector<Node::node*>, compare> minheap;
    for(auto iter = occurences.begin(); iter != occurences.end(); ++iter){
        Node::node* Node = Node::CreateNewNode(iter->first, iter->second);
        minheap.push(Node);
    }

    return minheap;
}

void Codec::build_huffman_tree(const std::string& PlainText){
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

void Codec::build_huffman_codes(Node::node* root, std::string String){
    if(!root) return;

    if(root->ch != '$'){
        map_.insert({root->ch, String});
    }
    build_huffman_codes(root->left, String + "0");
    build_huffman_codes(root->right, String + "1");
}

std::string Codec::map_char_to_code(const std::string& PlainText){
    std::string result;
    for(const char& ch: PlainText){
        auto code = map_.find(ch);
        result += code->second;
    }

    return result;
}

std::string Codec::encode_string_huffman(const std::string& PlainText){
    build_huffman_tree(PlainText);
    build_huffman_codes(huffman_tree_, "");

    std::string result = map_char_to_code(PlainText);
    return result;
}

std::string Codec::decode_string_huffman(const std::string& CompressedString){
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

std::string encode_string_caesar3(const std::string& PlainText){
    std::string EncodedString;
    for(int i = 0; i < PlainText.size(); ++i){
        EncodedString.push_back(PlainText[i]+3);
    }
    return EncodedString;
}

std::string decode_string_caesar3(const std::string& EncodedString){
    std::string DecodedString;
    for(int i = 0; i < EncodedString.size(); i++){
        DecodedString.push_back(EncodedString[i] - 3);
    }
    return DecodedString;
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
