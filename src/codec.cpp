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


std::string Codec::encode_string(const std::string& PlainText){
    std::string EncodedString;
    // TODO: invoke encStrat.encode();
    return EncodedString;
}

std::string Codec::decode_string(const std::string& EncodedString){
    std::string DecodedString;
    // TODO: invoke encStrat.decode();
    return DecodedString;
}
