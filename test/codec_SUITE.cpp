#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <queue>
#include <memory>

#include "codec.h"
#include "huffman.h"
#include "caesar.h"
#include "HuffmanBytes.h"

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
    Huffman huffman;
    std::map<const char, int> Result = huffman.count_occurences(String);
    EXPECT_EQ(true, map_compare(ExpResult, Result));
}

TEST(CodecTest, EncodeDecodeHuffman){
    auto encStrat = std::make_unique<Huffman> ();
    Codec codec { std::move(encStrat) };
    std::string PlainText {"THIS IS A SENTENCE"};

    EXPECT_EQ(PlainText, codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, EncodeDecodeHuffmanAdvanced){
    auto encStrat = std::make_unique<Huffman> ();
    Codec codec { std::move(encStrat) };
    std::string PlainText {"THIS IS A SENTENCE with Spec!al chars"};

    EXPECT_EQ(PlainText, codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, BasicEncodingCaesar3) {
    auto encStrat = std::make_unique<Caesar> ();
    Codec codec { std::move(encStrat) };
    std::string PlainText = "abc";
    std::string exp_result = PlainText;
    for(auto& c : exp_result) c+=3;

    EXPECT_EQ(exp_result, codec.encode_string(PlainText));
    EXPECT_NE(PlainText, codec.encode_string(PlainText));
}

TEST(CodecTest, EncodingDecodingCaesar) {
    auto encStrat = std::make_unique<Caesar> ();
    Codec codec { std::move(encStrat) };

    std::string PlainText = "this is some plain text";

    EXPECT_EQ(PlainText,  codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, EncodingDecodingUtf8Caesar) {
    auto encStrat = std::make_unique<Caesar> ();
    Codec codec { std::move(encStrat) };

    std::string PlainText = "this is some plain text with %&%€!@";

    EXPECT_EQ(PlainText,  codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, EncodingDecodingCaesarShift5) {
    auto encStrat = std::make_unique<Caesar> (Caesar(5));
    Codec codec { std::move(encStrat) };

    std::string PlainText = "this is some plain text with %&%€!@";

    EXPECT_EQ(PlainText,  codec.decode_string(codec.encode_string(PlainText)));
}

TEST(CodecTest, EncodeDecodeHuffmanBytes){
    HuffmanBytes hb;
    std::string plainText {"Some Text to be encoded"};
    std::vector<std::byte> textInBytes{};
    textInBytes.reserve(plainText.size());
    for(const auto ch : plainText)
    {
        textInBytes.push_back(static_cast<std::byte>(ch));
    }
    auto decodedBytes = hb.decode(hb.encode(textInBytes));
    EXPECT_EQ(plainText.size(), decodedBytes.size());

    std::string result{};
    result.reserve(decodedBytes.size());
    for(const auto& b : decodedBytes)
    {
        result.push_back(static_cast<char>(b));
    }
    EXPECT_EQ(plainText, result);
}

TEST(CodecTest, EncodeDecodeHuffmanBytesUtf8){
    HuffmanBytes hb;
    std::string plainText {"this is some plain text with %&%€!@"};
    std::vector<std::byte> textInBytes{};
    textInBytes.reserve(plainText.size());
    for(const auto ch : plainText)
    {
        textInBytes.push_back(static_cast<std::byte>(ch));
    }
    auto decodedBytes = hb.decode(hb.encode(textInBytes));
    EXPECT_EQ(plainText.size(), decodedBytes.size());

    std::string result{};
    result.reserve(decodedBytes.size());
    for(const auto& b : decodedBytes)
    {
        result.push_back(static_cast<char>(b));
    }
    EXPECT_EQ(plainText, result);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}