#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <queue>
#include <memory>

#include "codec.h"
#include "caesar.h"
#include "Huffman.h"
#include "FileReader.h"

template <typename CodecStratT>
struct CodecTest : public testing::Test {};

using CodecStrats = ::testing::Types</*Caesar,*/ Huffman>;
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

namespace
{
    std::vector<std::bitset<8>> stringToBits(const std::string& str)
    {
        uint8_t tmp{};
        std::vector<std::bitset<8>> result{};
        int count{};
        for(const auto ch : str)
        {
            if(ch == '0')
            {
                tmp &= 0xfe; // 1111 1110
            }
            else
            {
                tmp |= 0x01; // 0000 0001
            }
            if(count == 7)
            {
                result.push_back(std::bitset<8>(tmp));
                count = 0;
                tmp = 0;
            }
            else
            {
                tmp = tmp << 1;
                ++count;
            }
        }
        return result;
    }
}

TEST(bitTest, basic)
{
    std::vector<std::bitset<8>> expected{0xE8};
    const auto actual = stringToBits("11101000");
    EXPECT_EQ(actual, expected);
}

TEST(bitTest, basicVector)
{
    std::vector<std::bitset<8>> expected{0xE8, 0xE8};
    const auto actual = stringToBits("1110100011101000");
    EXPECT_EQ(actual, expected);
}

TYPED_TEST(CodecTest, EncodeFromFile)
{
    Codec codec {TypeParam{}};
    const std::string fileName = "../data/test.txt";
    FileReader fr{};
    const auto plainText = fr.readFile(fileName);
    const auto encodedString = codec.encodeFromFile(fileName);
    std::cout << "encodedString" << encodedString << "\n";
    //stringToBits(encodedString);
    EXPECT_EQ(plainText, codec.decode(fr.readFile("../data/out.txt")));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}