#ifndef TREE_H
#define TREE_H


typedef char* Elem_t;
struct Node
{
    Elem_t data = nullptr;
    Node *dad = nullptr;
    Node *right_son = nullptr;
    Node *left_son = nullptr;
};

struct Tree
{
    Node *root = nullptr;
    int size = 0;
};

Node *Op_new(Tree *tree, const char *str);
Node *Tree_insert(Tree *tree, Node *node, char *str);
void Node_dump(Node *node, FILE *fp);
void Tree_dump(Node *node);
void Print_nodes(Node *node, FILE *fp);
void Tree_dtor(Node *node);
void Get_new_file(Tree *tree);


#endif
