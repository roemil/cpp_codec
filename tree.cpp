#include "include/tree.h"
#include <iostream>

Tree::Tree(){
    root_ = nullptr;
    size_ = 0;
}

void Tree::delete_tree(node* Node){
    if(Node != nullptr){
        delete_tree(Node->left);
        delete_tree(Node->right);
        delete Node;
    }
}

Tree::~Tree(){
    delete_tree(root_);
}

node* Tree::GetNewNode(char ch, int freq){
    node* Node = new node;
    Node->ch = ch;
    Node->freq = freq;
    Node->left = Node->right = nullptr;
    size_++;
    return Node;
}

node* Tree::insert(node* Node, char ch, int freq){
    if(Node == nullptr){
        node* NewNode = GetNewNode(ch, freq);
        return NewNode;
    }else if(freq <= Node->freq){
        if(Node->left != nullptr){
            insert(Node->left, ch, freq);
        }else{
            Node->left = GetNewNode(ch, freq);
            Node->left->left = nullptr;
            Node->left->right = nullptr;
        }
    }else{
        if(Node->right != nullptr){
            insert(Node->right, ch, freq);
        }else{
            Node->right = GetNewNode(ch, freq);
            Node->right->left = nullptr;
            Node->right->right = nullptr;
        }
    }
    return Node;
}

void Tree::insert(char ch, int freq){
    root_ = insert(root_, ch, freq);
}

int Tree::get_freq(node* Node){
    return Node->freq;
}

int Tree::get_ch(node* Node){
    return Node->ch;
}

void Tree::print_tree(node* Node){
    if(Node != nullptr){
        std::cout << "Ch: " << Node->ch << " Freq: " << Node->freq << std::endl;
        print_tree(Node->left);
        print_tree(Node->right);
    }
}

void Tree::print_tree(){
    print_tree(root_);
}

int Tree::size(){
    return size_;
}

node* Tree::get_root(){
    return root_;
}
