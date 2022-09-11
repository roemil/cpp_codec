#ifndef TREE_H
#define TREE_H

struct node{
        char ch;
        int freq;
        node* left;
        node* right;
};

class Tree
{
private:
    node* root_;
    int size_;
    node* insert(node* Node, char ch, int freq);
    void print_tree(node* Node);
    void delete_tree(node* Node);
public:
    Tree();
    Tree(node* root);
    ~Tree();
    void insert(char ch, int freq);
    int get_freq(node* Node);
    int get_ch(node* Node);
    void print_tree();
    void delete_tree();
    int size();
    node* get_root();
    node* GetNewNode(char ch, int freq);
    void traverse_tree();
    void traverse_tree(node* root);
};

#endif