#include "include/node.h"
#include <iostream>


Node::node* Node::CreateNewNode(char ch, int freq){
    Node::node* n = new Node::node;
    n->ch = ch;
    n->freq = freq;
    n->left = n->right = nullptr;
    return n;
}


int get_freq(Node::node* n){
    return n->freq;
}

int get_ch(Node::node* n){
    return n->ch;
}