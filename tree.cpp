#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#include "tree.h"
#include "akinator.h"


Node *Tree_insert(Tree *tree, Node *node, char *str)
{
    if(tree->root == nullptr)
    {
        tree->root = (Node *)calloc(1, sizeof(Node));

        tree->root->data = (char *)calloc(AKINATOR_SIZE, sizeof(char));
        strcpy(tree->root->data, str);

        tree->root->right_son = nullptr;
        tree->root->left_son = nullptr;

        return tree->root;
    }

    if(node == nullptr)
    {
        node = (Node *)calloc(1, sizeof(Node));

        if(node == nullptr)
            abort();

        node->data = (char *)calloc(AKINATOR_SIZE, sizeof(char));
    }
    strcpy(node->data, str);

    node->right_son = nullptr;
    node->left_son = nullptr;

    return node;
}

void Print_nodes(Node *node, FILE *fp)
{
    if(node == nullptr)
    {
        fprintf(fp, "_ ");
        return;
    }

    fprintf(fp, "(");

    fprintf(fp, "\"%s\" ", node->data);

    Print_nodes(node->left_son, fp);
    Print_nodes(node->right_son, fp);

    fprintf(fp, ")");
}

void Tree_dtor(Node *node)
{
    if(node == nullptr)
        return;

    Tree_dtor(node->left_son);
    Tree_dtor(node->right_son);

    free(node);
}

void Node_dump(Node *node, FILE *fp)
{
    if(node == nullptr)
        return;

    fprintf(fp, "   node_%p [label = \"%s\"];\n", node, node->data);

    if(node->left_son != nullptr)
        fprintf(fp, "   node_%p -> node_%p;\n", node, node->left_son);

    Node_dump(node->left_son, fp);

    if(node->right_son != nullptr)
        fprintf(fp, "   node_%p -> node_%p;\n", node, node->right_son);

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





