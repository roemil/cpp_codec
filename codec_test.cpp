#include <gtest/gtest.h>
#include "include/types.h"
#include "include/codec.h"
#include "include/tree.h"
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

/*
* TEST LIST
* Compress simple string
* Decompress simple string
* Build a binary tree
* Fill binary tree
* Traverse binary tree to build string
*/

TEST(CodecTest, BitSetTest){
    std::bitset<5> BitSet {"1010"};
    EXPECT_EQ(0xA, BitSet);
}

template <typename Map>
bool map_compare (Map const &lhs, Map const &rhs) {
    // No predicate needed because there is operator== for pairs already.
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(),
                      rhs.begin());
}

TEST(CodecTest, OccurenceCount){
    // reverse iterator 
  EncryptionType enc_type = Huffman;
  Codec codec(enc_type);
  std::string String {"AAbbbccd"};
  std::map<const char, int> ExpResult {{'b', 3},
                                       {'c', 2},
                                       {'A', 2},
                                       {'d', 1}};
  std::map<const char, int> Result = count_occurences(String);
  EXPECT_EQ(true, map_compare(ExpResult, Result));
}

bool is_tree_equal(node* lNode, node* rNode){
    if(lNode == nullptr && rNode == nullptr){
        return true;
    }else if(lNode->freq == rNode->freq && lNode->ch == rNode->ch){
        if(is_tree_equal(lNode->left, rNode->left) &&
           is_tree_equal(lNode->right, rNode->right)){
            return true;
           }else{
            return false;
           }
    }else{
        return false;
    }
}

template <typename Tree>
bool tree_compare (Tree &lhs, Tree &rhs) {
    // No predicate needed because there is operator== for pairs already.
    node* lRoot = lhs.get_root();
    node * rRoot = rhs.get_root();
    return lhs.size() == rhs.size() && is_tree_equal(lRoot, rRoot);
}

TEST(CodecTest, BasicEncodingHuffman){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    std::string String {"BCAADDDCCACACAC"};

    std::string CompressionResult = codec.encode_string(String);
    std::string ExpResult = "1000111110110110100110110110";
    EXPECT_EQ(ExpResult, CompressionResult);
}

TEST(CodecTest, BasicDecodingHuffman){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    std::string String {"1000111110110110100110110110"};
    std::string ExpResult {"BCAADDDCCACACAC"};
    codec.build_huffman_tree(ExpResult);

    std::string CompressionResult = codec.decode_string(String);
    EXPECT_EQ(ExpResult, CompressionResult);
}

TEST(CodecTest, EncodeDecodeHuffman){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    std::string PlainText {"THIS IS A SENTENCE"};

    EXPECT_EQ(PlainText, codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, EncodeDecodeHuffmanAdvanced){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    std::string PlainText {"THIS IS A SENTENCE with Spec!al chars"};

    EXPECT_EQ(PlainText, codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, CompareTrees){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    Tree TreeA;
    TreeA.insert('A', 3);
    TreeA.insert('b', 3);
    TreeA.insert('c', 2);
    TreeA.insert('d', 1);
    TreeA.insert('e', 5);

    Tree TreeB;
    TreeB.insert('A', 3);
    TreeB.insert('b', 3);
    TreeB.insert('c', 2);
    TreeB.insert('d', 1);
    TreeB.insert('e', 5);

    EXPECT_EQ(5, TreeA.size());
    EXPECT_EQ(true, tree_compare(TreeA, TreeB));

}

TEST(CodecTest, BasicEncodingCaesar3) {
  EncryptionType enc_type = Caesar3;
  Codec codec(Caesar3);
  std::string PlainText = "abc";
  std::string exp_result = PlainText;
  for(auto& c : exp_result) c+=3;

  EXPECT_EQ(exp_result, codec.encode_string(PlainText));
  EXPECT_NE(PlainText, codec.encode_string(PlainText));
}

TEST(CodecTest, EncodingDecodingCaesar) {
  EncryptionType enc_type = Caesar3;
  Codec codec(Caesar3);

  std::string PlainText = "this is some plain text";

  EXPECT_EQ(PlainText,  codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, EncodingDecodingUtf8Caesar) {
  EncryptionType enc_type = Caesar3;
  Codec codec(Caesar3);

  std::string PlainText = "this is some plain text with %&%€!@";

  EXPECT_EQ(PlainText,  codec.decode_string(codec.encode_string(PlainText)));
}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}