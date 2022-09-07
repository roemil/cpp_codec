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
    node* insert(node* Node, char ch, int freq);
    node* GetNewNode(char ch, int freq);
    void print_tree(node* Node);
    void delete_tree(node* Node);
public:
    Tree();
    ~Tree();
    void insert(char ch, int freq);
    int get_freq();
    void print_tree();
    void delete_tree();
};

#endif