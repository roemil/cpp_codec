#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <queue>
#include <memory>

#include "codec.h"
#include "caesar.h"
#include "Huffman.h"

ByteVector stringToByteVector(const std::string& str)
{
    std::vector<std::byte> textInBytes{};
    textInBytes.reserve(str.size());
    for(const auto ch : str)
    {
        textInBytes.push_back(static_cast<std::byte>(ch));
    }
    return textInBytes;
}

std::string byteVectorToString(const ByteVector& bv)
{
    std::string str{};
    str.reserve(bv.size());
    for(const auto& b : bv)
    {
        str.push_back(static_cast<char>(b));
    }
    return str;
}

TEST(CodecTest, BasicEncodingCaesar3) {
    auto encStrat = Caesar ();
    Codec codec { encStrat };
    std::string plainText = "abc";
    const auto textInBytes = stringToByteVector(plainText);

    EXPECT_EQ(plainText, byteVectorToString(codec.decode(codec.encode(textInBytes))));
}

TEST(CodecTest, EncodingDecodingCaesar) {
    auto encStrat = Caesar ();
    Codec codec { encStrat};

    std::string plainText = "this is some plain text";
    const auto textInBytes = stringToByteVector(plainText);

    EXPECT_EQ(plainText, byteVectorToString(codec.decode(codec.encode(textInBytes))));
}

TEST(CodecTest, EncodingDecodingUtf8Caesar) {
    auto encStrat = Caesar{};
    Codec codec { encStrat };

    std::string plainText = "this is some plain text with %&%€!@";
    const auto textInBytes = stringToByteVector(plainText);

    EXPECT_EQ(plainText, byteVectorToString(codec.decode(codec.encode(textInBytes))));
}

TEST(CodecTest, EncodingDecodingCaesarShift5) {
    auto encStrat = Caesar(5);
    Codec codec { encStrat };

    std::string plainText = "this is some plain text with %&%€!@";
    const auto textInBytes = stringToByteVector(plainText);

    EXPECT_EQ(plainText, byteVectorToString(codec.decode(codec.encode(textInBytes))));
}

TEST(CodecTest, EncodeDecodeHuffmanBytes){
    Huffman huffman;
    Codec codec { huffman };
    std::string plainText {"Some Text to be encoded"};
    const auto textInBytes = stringToByteVector(plainText);
    EXPECT_EQ(plainText, byteVectorToString(codec.decode(codec.encode(textInBytes))));
}

TEST(CodecTest, EncodeDecodeHuffmanBytesUtf8){
    Huffman huffman;
    Codec codec { huffman };
    std::string plainText {"this is some plain text with %&%€!@"};
    const auto textInBytes = stringToByteVector(plainText);
    EXPECT_EQ(plainText, byteVectorToString(codec.decode(codec.encode(textInBytes))));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}