#include <gtest/gtest.h>
#include "include/codec.h"
#include <iostream>

/*
* TEST LIST
* Compress simple string
* Decompress simple string
* Build a binary tree
* Fill binary tree
* Traverse binary tree to build string
*/

TEST(CodecTest, CompressSimpleString){
  EncryptionType enc_type = Huffman;
  Codec codec(Huffman);
  std::string PlainText = "abc";
  ByteVector ExpResult = {'3', '2', '1'};
  EXPECT_EQ(ExpResult, codec.compress_string(PlainText));
}

template <typename Map>
bool map_compare (Map const &lhs, Map const &rhs) {
    // No predicate needed because there is operator== for pairs already.
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(),
                      rhs.begin());
}

TEST(CodecTest, OccurenceCount){
  EncryptionType enc_type = Huffman;
  Codec codec(Huffman);
  std::string String {"AAAbbbccd"};
  std::map<const char, int> ExpResult;
  ExpResult.insert({'A', 3});
  ExpResult.insert({'b', 3});
  ExpResult.insert({'c', 2});
  ExpResult.insert({'d', 1});
  std::map<const char, int> Result = codec.count_occurences(String);
  EXPECT_EQ(true, map_compare(ExpResult, Result));
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