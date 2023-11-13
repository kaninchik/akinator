#ifndef TREE_H
#define TREE_H


typedef int Elem_t;
struct Node
{
    Elem_t data = 0;
    Node *right_son = nullptr;
    Node *left_son = nullptr;
};

struct Tree
{
    Node *root = nullptr;
    int size = 0;
};

Node *Op_new(Tree *tree, int value);
void Tree_insert(Tree *tree, int value);
void Node_dump(Node *node, FILE *fp);
void Tree_dump(Node *node);
void Print_nodes(Node *node);
void Tree_dtor(Node *node);


#endif
