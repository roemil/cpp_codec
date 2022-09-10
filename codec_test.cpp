#include <gtest/gtest.h>
#include "include/types.h"
#include "include/codec.h"
#include "include/tree.h"
#include <iostream>

/*
* TEST LIST
* Compress simple string
* Decompress simple string
* Build a binary tree
* Fill binary tree
* Traverse binary tree to build string
*/


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
  Codec codec(Huffman);
  std::string String {"AAAbbbccd"};
  std::map<const char, int> ExpResult {{'A', 3},
                                       {'b', 3},
                                       {'c', 2},
                                       {'d', 1}};
  std::map<const char, int> Result = codec.count_occurences(String);
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

TEST(CodecTest, BasicBinaryTree){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    Tree ExpTree;
    ExpTree.insert('d', 1);
    ExpTree.insert('c', 2);
    ExpTree.insert('b', 3);
    ExpTree.insert('A', 3);
    std::string String {"AAAbbbccd"};

    Tree OccuranceTree = codec.build_min_heap(String);

    EXPECT_EQ(true, tree_compare(ExpTree, OccuranceTree));
}

TEST(CodecTest, BasicCompression){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    std::string String {"BCAADDDCCACACAC"};
    // 100 0 11 11 101 101 0 0 11 0 11 0 11 0

    std::string CompressionResult = codec.compress_string(String);
    std::string ExpResult = "1000111110110100110110110";
    EXPECT_EQ(ExpResult, CompressionResult);
}

TEST(CodecTest, CompareTrees){
    EncryptionType enc_type = Huffman;
    Codec codec(Huffman);
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

TEST(CodecTest, EncodingDecoding) {
  EncryptionType enc_type = Caesar3;
  Codec codec(Caesar3);

  std::string PlainText = "this is some plain text";

  EXPECT_EQ(PlainText,  codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, EncodingDecodingUtf8) {
  EncryptionType enc_type = Caesar3;
  Codec codec(Caesar3);

  std::string PlainText = "this is some plain text with %&%€!@";

  EXPECT_EQ(PlainText,  codec.decode_string(codec.encode_string(PlainText)));
}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}