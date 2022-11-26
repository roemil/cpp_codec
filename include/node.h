#ifndef NODE_H
#define NODE_H

namespace Node{
struct node{
        char ch;
        int freq;
        node* left;
        node* right;
};

int get_freq(node* Node);
int get_ch(node* Node);
node* CreateNewNode(char ch, int freq);
}

#endif