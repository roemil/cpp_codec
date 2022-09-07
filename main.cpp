
#include "include/tree.h"
#include "include/codec.h"
#include "include/types.h"
#include <iostream>

int main(){
    std::string String {"AAAbbbccd"};
    Codec codec(Huffman);
    Tree OccuranceTree = codec.build_tree(String);
    OccuranceTree.print_tree();
    std::cout << std::endl;
    Tree ExpTree;
    ExpTree.insert('d', 1);
    ExpTree.insert('c', 2);
    ExpTree.insert('b', 3);
    ExpTree.insert('A', 3);
    ExpTree.print_tree();

    return 0;
}