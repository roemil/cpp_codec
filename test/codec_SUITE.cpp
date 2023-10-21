#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <queue>
#include <memory>

#include "codec.h"
#include "caesar.h"
#include "Huffman.h"

template <typename CodecStratT>
struct CodecTest : public testing::Test {};

using CodecStrats = ::testing::Types<Caesar, Huffman>;
TYPED_TEST_SUITE(CodecTest, CodecStrats);

TYPED_TEST(CodecTest, EncodeDecodeSimple){
    Codec codec {TypeParam{}};
    std::string plainText {"Some Text to be encoded"};
    const auto encoded = codec.encode(plainText);
    EXPECT_EQ(plainText, codec.decode(encoded));
}

TYPED_TEST(CodecTest, EncodeDecodeUtf8){
    Codec codec {TypeParam{}};
    std::string plainText {"this is some plain text with %&%€!@"};
    EXPECT_EQ(plainText, codec.decode(codec.encode(plainText)));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}