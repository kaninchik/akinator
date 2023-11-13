#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#include "tree.h"


Node *Op_new(Tree *tree, int value)
{
    assert(tree != nullptr);

    Node *node =  (Node *)calloc(1, sizeof(Node));   //или лучше сделать, чтобы изначально выделялось некоторое коо-во узлов?
    node->data = value;
    node->right_son = nullptr;
    node->left_son = nullptr;

    tree->size++;

    return node;
}

void Tree_insert(Tree *tree, int value)
{
    if(tree->root == nullptr)
    {
        tree->root = (Node *)calloc(1, sizeof(Node));
        tree->root->data = value;
        tree->root->right_son = nullptr;
        tree->root->left_son = nullptr;
        return;
    }

    Node *caront = tree->root;
    Node *new_node = Op_new(tree, value);

    while(true)
    {
        if(value >= caront->data)
        {
            if(caront->right_son == nullptr)
            {
                caront->right_son = new_node;
                break;
            }
            else
                caront = caront->right_son;
        }
        else if(value < caront->data)
        {
            if(caront->left_son == nullptr)
            {
                caront->left_son = new_node;
                break;
            }
            else
                caront = caront->left_son;
        }
    }
    return;
}

void Print_nodes(Node *node)
{
    if(node == nullptr)
    {
        printf("nil ");
        return;
    }
    printf("(");

    printf("%d ", node->data);
    Print_nodes(node->left_son);
    Print_nodes(node->right_son);

    printf(")");
}

void Tree_dtor(Node *node)
{
    if(node == nullptr)
        return;

    free(node);

    Tree_dtor(node->left_son);
    Tree_dtor(node->right_son);
}

void Node_dump(Node *node, FILE *fp)
{
    if(node == nullptr)
        return;

    fprintf(fp, "   node_%p [label = \"%d\"]\n", node, node->data);

    if(node->left_son != nullptr)
        fprintf(fp, "   node_%p -> node_%p\n", node, node->left_son);

    Node_dump(node->left_son, fp);

    if(node->right_son != nullptr)
        fprintf(fp, "   node_%p -> node_%p\n", node, node->right_son);

    Node_dump(node->right_son, fp);
}

void Tree_dump(Node *node)
{
    FILE *fp = fopen("tree_dump.dot", "w+");

    fprintf(fp, "digraph G                                         \n"
                "{                                                 \n"
                "   graph [bgcolor = \"#ffcbdb\"]                  \n"
                "   rankdir = TB;                                  \n"
                "   node [style = \"filled\", shape = circle];     \n");

    Node_dump(node, fp);

    fprintf(fp, "}\n");

    fclose(fp);
}





