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
struct CodecTest : public testing::Test
{
};

using CodecStrats = ::testing::Types<Caesar, Huffman>;
TYPED_TEST_SUITE(CodecTest, CodecStrats);

TYPED_TEST(CodecTest, EncodeDecodeSimple)
{
    Codec codec{TypeParam{}};
    std::string plainText{"Some Text to be encoded"};
    const auto encoded = codec.encode(plainText);
    EXPECT_EQ(plainText, codec.decode(encoded));
}

TYPED_TEST(CodecTest, EncodeDecodeUtf8)
{
    Codec codec{TypeParam{}};
    std::string plainText{"this is some plain text with %&%€!@"};
    EXPECT_EQ(plainText, codec.decode(codec.encode(plainText)));
}

namespace
{
    std::vector<uint8_t> stringToBits(const std::string &str)
    {
        uint8_t tmp{};
        std::vector<uint8_t> result{};
        int count{};
        for (const auto ch : str)
        {
            if (ch == '0')
            {
                tmp &= 0xfe; // 1111 1110
            }
            else if(ch == '1')
            {
                tmp |= 0x01; // 0000 0001
            }
            else
            {
                // normal char
                result.push_back(static_cast<uint8_t>(ch));
                continue;
            }
            if (count == 7)
            {
                result.push_back(tmp);
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

    std::string bitsToString(const std::vector<uint8_t> &byteString)
    {
        std::string result{};
        result.reserve(byteString.size());
        for (const auto &byte : byteString)
        {
            const auto bitSet = std::bitset<8>(byte);
            result += bitSet.to_string();
        }
        return result;
    }

    std::string charsToString(const std::vector<uint8_t> &byteString)
    {
        // TODO: This should really be in FileReader
        // or somewhere else
        std::string result{};
        result.reserve(byteString.size());
        for (const auto &byte : byteString)
        {
            result += static_cast<char>(byte);
        }
        return result;
    }
}

TEST(bitTest, basic)
{
    std::vector<uint8_t> expected{0xE8};
    const auto actual = stringToBits("11101000");
    EXPECT_EQ(actual, expected);
}

TEST(bitTest, bitsToString)
{
    std::vector<uint8_t> expected{0xE8};
    const std::string bitString{"11101000"};
    const std::vector<uint8_t> actual = stringToBits(bitString);
    EXPECT_EQ(actual, expected);

    const auto string = bitsToString(expected);
    EXPECT_EQ(bitString, string);
}

TEST(bitTest, basicVector)
{
    std::vector<uint8_t> expected{0xE8, 0xE8};
    const auto actual = stringToBits("1110100011101000");
    EXPECT_EQ(actual, expected);
}

TYPED_TEST(CodecTest, EncodeDecodeFromFile)
{
    Codec codec{TypeParam{}};
    const std::string fileName = "../data/test.txt";
    FileReader fr{};
    const auto plainText = fr.readFile(fileName);

    // Act
    const auto encodedString = codec.encodeFromFile(fileName);
    const auto bitString = stringToBits(encodedString);
    fr.writeToFile(bitString);

    // Assert
    const auto bitStringDecoded = fr.readBinaryFile("../data/out.bin");
    if(std::is_same_v<TypeParam, Huffman>)
    {
        EXPECT_EQ(plainText, codec.decode(bitsToString(bitStringDecoded)));
    }
    else
    {
        EXPECT_EQ(plainText, codec.decode(charsToString(bitStringDecoded)));
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}