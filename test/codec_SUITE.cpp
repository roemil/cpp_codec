#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <memory>

#include "types.h"
#include "codec.h"
#include "huffman.h"
#include "caesar.h"

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

/* TEST(CodecTest, OccurenceCount){ TODO Fix
  std::string String {"AAbbbccd"};
  std::map<const char, int> ExpResult {{'b', 3},
                                       {'c', 2},
                                       {'A', 2},
                                       {'d', 1}};
  std::map<const char, int> Result = Huffman::count_occurences(String);
  EXPECT_EQ(true, map_compare(ExpResult, Result));
} */

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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}