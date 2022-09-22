#include <gtest/gtest.h>
#include "types.h"
#include "codec.h"
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

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
  std::string String {"AAbbbccd"};
  std::map<const char, int> ExpResult {{'b', 3},
                                       {'c', 2},
                                       {'A', 2},
                                       {'d', 1}};
  std::map<const char, int> Result = Utility::count_occurences(String);
  EXPECT_EQ(true, map_compare(ExpResult, Result));
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