#include <cstdio>

#include "tree.h"

int main()
{
    Tree tree = {};

    Tree_insert(&tree, 10);
    Tree_insert(&tree, 5);
    Tree_insert(&tree, 15);
    Tree_insert(&tree, 12);
    Tree_insert(&tree, 20);
    Tree_insert(&tree, 11);
    Tree_insert(&tree, 3);
    Tree_insert(&tree, 16);
    Tree_insert(&tree, 7);

    Tree_dump(tree.root);
    Tree_dtor(tree.root);

    return 0;
}

