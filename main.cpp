#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#include "tree.h"
#include "akinator.h"

Node *DEAD_PTR = (Node *)333;

int main()
{
    Tree tree = {};

    char *buffer = Get_file_content();
    Fucking_filling_function(&tree, &tree.root, DEAD_PTR, &buffer);

    Get_comparison(&tree);

    Tree_dump(tree.root);
    Tree_dtor(tree.root);

    return 0;
}
