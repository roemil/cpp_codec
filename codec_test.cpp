#include <gtest/gtest.h>
#include "include/codec.h"
#include <iostream>

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