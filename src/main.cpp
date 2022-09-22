
#include "include/tree.h"
#include "include/codec.h"
#include "include/types.h"
#include <iostream>

int main(){
    // std::string String {"AAAbbbccd"};
    // Codec codec(Huffman);
    // Tree OccuranceTree = codec.build_min_heap(String);
    // OccuranceTree.print_tree();
    // std::cout << std::endl;
    // Tree ExpTree;
    // ExpTree.insert('d', 1);
    // ExpTree.insert('c', 2);
    // ExpTree.insert('b', 3);
    // ExpTree.insert('A', 3);
    // ExpTree.print_tree();

    std::cout << std::endl;
    std::string String {"BCAADDDCCACACAC"};
    Codec codec(Huffman);
    std::string Result = codec.compress_string(String);
    std::cout << Result << std::endl;

    return 0;
}