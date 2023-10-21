#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <queue>
#include <memory>

#include "codec.h"
#include "caesar.h"
#include "Huffman.h"

TEST(CodecTest, BasicEncodingCaesar3) {
    auto encStrat = Caesar ();
    Codec codec { encStrat };
    std::string plainText = "abc";

    EXPECT_EQ(plainText, codec.decode(codec.encode(plainText)));
}

TEST(CodecTest, EncodingDecodingCaesar) {
    auto encStrat = Caesar ();
    Codec codec { encStrat};

    std::string plainText = "this is some plain text";

    EXPECT_EQ(plainText, codec.decode(codec.encode(plainText)));
}

TEST(CodecTest, EncodingDecodingUtf8Caesar) {
    auto encStrat = Caesar{};
    Codec codec { encStrat };

    std::string plainText = "this is some plain text with %&%€!@";

    EXPECT_EQ(plainText, codec.decode(codec.encode(plainText)));
}

TEST(CodecTest, EncodingDecodingCaesarShift5) {
    auto encStrat = Caesar(5);
    Codec codec { encStrat };

    std::string plainText = "this is some plain text with %&%€!@";

    EXPECT_EQ(plainText, codec.decode(codec.encode(plainText)));
}

TEST(CodecTest, EncodeDecodeHuffmanBytes){
    Huffman huffman;
    Codec codec { huffman };
    std::string plainText {"Some Text to be encoded"};
    EXPECT_EQ(plainText, codec.decode(codec.encode(plainText)));
}

TEST(CodecTest, EncodeDecodeHuffmanBytesUtf8){
    Huffman huffman;
    Codec codec { huffman };
    std::string plainText {"this is some plain text with %&%€!@"};
    EXPECT_EQ(plainText, codec.decode(codec.encode(plainText)));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}