#include "include/codec.h"
#include <map>

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

Tree Codec::build_tree(const std::string& PlainText){
    std::map<const char, int> occurences = count_occurences(PlainText);
    Tree OccuranceTree;
    for(auto iter = occurences.begin(); iter != occurences.end(); ++iter){
        OccuranceTree.insert(iter->first, iter->second);
    }
    return OccuranceTree;
}

ByteVector Codec::compress_string(const std::string& PlainText){
    //std::map<const char, int> occurences = count_occurences(PlainText);
    ByteVector CompressedString {'3', '2', '1'};
    return CompressedString;
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
