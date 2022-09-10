#include "include/codec.h"
#include <map>
#include <unordered_map>
#include <iostream>

Codec::Codec(EncryptionType EncType)
{
    enc_type_ = EncType;
}

Codec::~Codec()
{
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
        default:
            return "";
    }
    return EncodedString;
    
}

std::map<const char, int> Codec::count_occurences(const std::string& PlainText){
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

Tree Codec::build_min_heap(const std::string& PlainText){
    std::map<const char, int> occurences = count_occurences(PlainText);
    Tree OccuranceTree;
    for(auto iter = occurences.rbegin(); iter != occurences.rend(); ++iter){
        OccuranceTree.insert(iter->first, iter->second);
    }
    return OccuranceTree;
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

std::string Codec::compress_string(const std::string& PlainText){
    std::map<const char, int> occurences = count_occurences(PlainText);
    Tree BTree;
    std::vector<node*> NodeVector;
    for(auto iter = occurences.begin(); iter != occurences.end(); ++iter){
        node* NewNode = BTree.GetNewNode(iter->first, iter->second);
        NodeVector.push_back(NewNode);
    }

    while(NodeVector.size() != 1){
        node* Left = NodeVector.back();
        NodeVector.pop_back();
        node* Right = NodeVector.back();
        NodeVector.pop_back();
        node* NewNode = BTree.GetNewNode('$', Left->freq+Right->freq);
        NewNode->left = Left;
        NewNode->right = Right;
        NodeVector.push_back(NewNode);
    }
    print_huffman(NodeVector.back(), "");
    build_huffman_codes(NodeVector.back(), "");
    std::string result;
    for(const char& ch: PlainText){
        auto code = map_.find(ch);
        std::cout << "Ch : " << ch << "Code: " << code->second << std::endl;
        result += code->second;
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
    default:
        DecodedString = "";
        break;
    }
    return DecodedString;
}
