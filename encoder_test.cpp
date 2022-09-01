#include <gtest/gtest.h>
#include "include/encoder.h"
#include "include/decoder.h"
#include <iostream>

TEST(CodecTest, BasicEncodingCaesar3) {
  EncryptionType enc_type = Caesar3;
  encoder enc(Caesar3);
  std::string PlainText = "abc";
  std::string exp_result = PlainText;
  for(auto& c : exp_result) c+=3;

  EXPECT_EQ(exp_result, enc.encode_string(PlainText));
  EXPECT_NE(PlainText, enc.encode_string(PlainText));
}

TEST(CodecTest, EncodingDecoding) {
  EncryptionType enc_type = Caesar3;
  encoder enc(Caesar3);
  decoder dec(Caesar3);

  std::string PlainText = "this is some plain text";

  EXPECT_EQ(PlainText,  dec.decode_string(enc.encode_string(PlainText)));
}

TEST(CodecTest, EncodingDecodingUtf8) {
  EncryptionType enc_type = Caesar3;
  encoder enc(Caesar3);
  decoder dec(Caesar3);

  std::string PlainText = "this is some plain text with %&%€!@";

  EXPECT_EQ(PlainText,  dec.decode_string(enc.encode_string(PlainText)));
}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}