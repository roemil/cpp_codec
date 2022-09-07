
#include "include/tree.h"
#include <iostream>

int main(){
    Tree TreeA;
    TreeA.insert('A', 3);
    TreeA.insert('b', 3);
    TreeA.insert('c', 2);
    TreeA.insert('d', 4);
    TreeA.insert('e', 5);

    TreeA.print_tree();

    return 0;
}