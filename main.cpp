#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>

#include "tree.h"
#include "akinator.h"

int main()
{
    Tree tree = {};

    char *buffer = Get_file_content();

    Fucking_filling_function(&tree.root, &buffer); //походу, правому сыну пиздец. левый жесткий братанчик, держится

    printf("right_son = %p\n", tree.root->right_son); // указатель нуль(ЛЮБЛЮ ЕГО)

    Guess_object(&tree);

    Tree_dump(tree.root);
    Tree_dtor(tree.root);

    return 0;
}
