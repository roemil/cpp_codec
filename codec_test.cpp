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
  Codec codec(Huffman);
  std::string String {"AAbbbccd"};
  std::map<const char, int> ExpResult {{'b', 3},
                                       {'c', 2},
                                       {'A', 2},
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

TEST(CodecTest, CompareMinHeap){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    Tree tree;
    std::priority_queue<node*, std::vector<node*>, compare> ExpMinHeap;
    ExpMinHeap.push(tree.GetNewNode('d', 1));
    ExpMinHeap.push(tree.GetNewNode('c', 2));
    ExpMinHeap.push(tree.GetNewNode('b', 3));
    ExpMinHeap.push(tree.GetNewNode('A', 3));

    std::string String {"AAAbbbccd"};
    std::priority_queue<node*, std::vector<node*>, compare> minheap = codec.build_min_heap(String);
    EXPECT_EQ(ExpMinHeap.size(), minheap.size());
    // TODO: Overload operator ==
    for(int i = 0; i < minheap.size(); ++i){
        auto ExpMinHeapTop = ExpMinHeap.top();
        auto minheaptop = minheap.top();
        EXPECT_EQ(ExpMinHeapTop->ch, minheaptop->ch);
        EXPECT_EQ(ExpMinHeapTop->freq, minheaptop->freq);
        ExpMinHeap.pop();
        minheap.pop();
    }
}

TEST(CodecTest, CompareMinHeapWithSpace){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    Tree tree;
    std::priority_queue<node*, std::vector<node*>, compare> ExpMinHeap;
    ExpMinHeap.push(tree.GetNewNode('d', 1));
    ExpMinHeap.push(tree.GetNewNode('c', 2));
    ExpMinHeap.push(tree.GetNewNode('b', 3));
    ExpMinHeap.push(tree.GetNewNode('A', 3));
    ExpMinHeap.push(tree.GetNewNode(' ', 4));

    std::string String {"AAA bbb cc d "};
    std::priority_queue<node*, std::vector<node*>, compare> minheap = codec.build_min_heap(String);
    EXPECT_EQ(ExpMinHeap.size(), minheap.size());
    // TODO: Overload operator ==
    for(int i = 0; i < minheap.size(); ++i){
        auto ExpMinHeapTop = ExpMinHeap.top();
        auto minheaptop = minheap.top();
        EXPECT_EQ(ExpMinHeapTop->ch, minheaptop->ch);
        EXPECT_EQ(ExpMinHeapTop->freq, minheaptop->freq);
        ExpMinHeap.pop();
        minheap.pop();
    }
}

TEST(CodecTest, BasicCompression){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    std::string String {"BCAADDDCCACACAC"};

    std::string CompressionResult = codec.compress_string(String);
    std::string ExpResult = "1000111110110110100110110110"; // should be bitset
    EXPECT_EQ(ExpResult, CompressionResult);
}

TEST(CodecTest, AdvancedCompressions){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    std::string String {"THIS IS A SENTENCE"};

    std::string CompressionResult = codec.compress_string(String);
    std::string ExpResult = "11010100011101111011101111010111110100100110100100110000";
    EXPECT_EQ(ExpResult, CompressionResult);
}

TEST(CodecTest, BasicDeCompress){
    EncryptionType enc_type = Huffman;
    Codec codec(enc_type);
    std::string CompressedString = "11010100011101111011101111010111110100100110100100110000";
    std::string ExpResult {"THIS IS A SENTENCE"};
    std::string String {"THIS IS A SENTENCE"};
    std::string CompressionResult = codec.compress_string(String);

    std::string DeCompressionResult = codec.decompress_string(CompressedString);

    EXPECT_EQ(ExpResult, DeCompressionResult);
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