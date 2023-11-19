#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cctype>
#include <sys/stat.h>

#include "tree.h"
#include "akinator.h"

size_t Get_file_size(FILE *fp)
{
    assert(fp != nullptr);

    struct stat st = {};

    fstat(fileno(fp), &st);

    return st.st_size;
}

char *Get_file_content()
{
    FILE *fp = fopen("akinator.txt", "rb");

    int file_size = Get_file_size(fp);

    char *buffer = (char *)calloc(file_size + 1, sizeof(char));

    size_t sym = fread(buffer, sizeof(char), file_size + 1, fp);

    fclose(fp);

    return buffer;
}

void Get_string(Node **node, char **buffer)
{
    assert(buffer != nullptr);

    (*node)->data = (char *)calloc(AKINATOR_SIZE, sizeof(char));

    if(**buffer == '(')
    {
        *buffer = *buffer + 1;
        if(**buffer == '"')
        {
            *buffer = *buffer + 1;
            sscanf(*buffer, "%[^\"]", (*node)->data);
            *buffer = *buffer + strlen((*node)->data) + 1;
        }
    }
}

void Fucking_filling_function(Node **node, char **buffer)
{
    if(**buffer == '(')
    {
        *node = (Node *)calloc(1, sizeof(Node));
        Get_string(node, buffer);
        (*node)->left_son = nullptr;
        (*node)->right_son = nullptr;
    }
    if(**buffer == ')')
    {
        int sym = 0;
        if(sscanf(*buffer + 1, "%d", &sym) == EOF)
            return;

        *buffer = *buffer + 1;
        return;
    }

    printf("GO LEFT SON %s\n", (*node)->data);
    Fucking_filling_function(&((*node)->left_son), buffer);
    printf("GO RIGHT SON %s\n", (*node)->data);
    Fucking_filling_function(&((*node)->right_son), buffer);
}

void Guess_object(Tree *tree)
{
    printf("Hello, a mere mortal! will you fight me? You have to make a character\n");

    Node *node = tree->root;

    char *answer = (char *)calloc(AKINATOR_SIZE, sizeof(char));
    assert(answer != nullptr);

    printf("It is necessary and sufficient for you to answer \"yes\" or \"no\"! No amateur activity!\n");

    while(node->left_son != nullptr || node->right_son != nullptr)
    {
        printf("Is your character %s?\n", node->data);

        printf("tree_root = %p\n left_son = %p\n right_son = %p\n", node->data, node->left_son->data, node->right_son->data);

        answer = Get_answer(answer);

        if(strncmp(answer, "yes", sizeof("yes")) == 0 || strncmp(answer, "Yes", sizeof("Yes")) == 0)
            node = node->left_son;
        else if(strncmp(answer, "no", sizeof("no")) == 0 || strncmp(answer, "No", sizeof("No")) == 0)
            node = node->right_son;
        else
            printf("Nice try. I advise you to be more careful and follow the instructions. A madcap...\n");
    }

    printf("Well, brother, you made %s wish?\n", node->data);

    answer = Get_answer(answer);

    if(strncmp(answer, "yes", sizeof("yes")) == 0 || strncmp(answer, "Yes", sizeof("Yes")) == 0)
    {
        printf("Well, loshara, I told you that you will never be able to achieve my power\n");
        return;
    }
    else
    {
        printf("What?? You're lying! Well, who was it?\n");

        char *object = (char *)calloc(AKINATOR_SIZE, sizeof(char));
        object = Get_answer(object);

        printf("Listen, bro...how does %s differ from %s\n", object, node->data);

        char *characteristic = (char *)calloc(AKINATOR_SIZE, sizeof(char));
        characteristic = Get_answer(characteristic);

        printf("Eh, okay...you won\n");
        printf("Since this is the case, I'll let you dominate me. Do you want to save your hero?\n");

        answer = Get_answer(answer);

        if(strncmp(answer, "yes", sizeof("yes")) == 0 || strncmp(answer, "Yes", sizeof("Yes")) == 0)
        {
            node->left_son = Tree_insert(tree, node->left_son, object);
            node->right_son = Tree_insert(tree, node->right_son, node->data);
            node->data = characteristic;

            Get_new_file(tree);
        }
        free(object);
        free(characteristic);
    }
    free(answer);

    return;
}

char *Get_answer(char *answer)
{
    assert(answer != nullptr);

    fgets(answer, AKINATOR_SIZE, stdin);

    int length = strlen(answer);
    answer[length - 1] = '\0';

    return answer;
}

void Get_new_file(Tree *tree)
{
    assert(tree != nullptr);

    FILE *fp = fopen("akinator.txt", "w+");

    Print_nodes(tree->root, fp);

    fclose(fp);
}


