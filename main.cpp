
#include "include/tree.h"
#include <iostream>

int main(){
    Tree BTree;
    BTree.insert('a', 1);
    BTree.insert('b', 2);
    BTree.insert('c', 3);
    BTree.insert('d', 2);

    BTree.print_tree();

    return 0;
}