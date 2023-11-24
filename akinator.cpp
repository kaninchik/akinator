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

bool Get_string(Node **node, char **buffer)
{
    assert(buffer != nullptr);

    if(**buffer == '(')
    {
        (*node)->data = (char *)calloc(AKINATOR_SIZE, sizeof(char));

        *buffer = *buffer + 1;
        if(**buffer == '"')
        {
            *buffer = *buffer + 1;

            sscanf(*buffer, "%[^\"]", (*node)->data);

            while(**buffer != '(' && **buffer != '_')
                *buffer = *buffer + 1;

            return true;
        }
    }
    else
    {
        while(**buffer != ')' && **buffer != '_')
            *buffer = *buffer + 1;

        return false;
    }
}

void Fucking_filling_function(Tree *tree, Node **node, Node *dad, char **buffer)
{
    if(**buffer == '(')
    {
        *node = (Node *)calloc(1, sizeof(Node));

        Get_string(node, buffer);

        (*node)->left_son = nullptr;
        (*node)->right_son = nullptr;

        if(*node != tree->root)
            (*node)->dad = dad;
        else
            (*node)->dad = nullptr;
    }
    else if(!Get_string(node, buffer))
    {
        *buffer = *buffer + 2;
        return;
    }

    Fucking_filling_function(tree, &((*node)->left_son), *node, buffer);
    Fucking_filling_function(tree, &((*node)->right_son), *node, buffer);

    if(**buffer == ')')
    {
        int sym = 0;
        if(sscanf(*buffer + 1, "%d", &sym) == EOF)
            return;

        *buffer = *buffer + 1;
        return;
    }
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

        answer = Get_answer(answer);

        if(strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0)
            node = node->left_son;
        else if(strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0)
            node = node->right_son;
        else
            printf("Nice try. I advise you to be more careful and follow the instructions. A madcap...\n");
    }

    printf("Well, brother, you made %s wish?\n", node->data);

    answer = Get_answer(answer);

    if(strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0)
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

        if(strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0)
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

void Find_node(Node *node, char *hero, Node **find)
{
    assert(hero != nullptr);

    if(strcmp(node->data, hero) == 0)
    {
        *find = node;
        return;
    }
    else
    {
        if(node->left_son != nullptr)
            Find_node(node->left_son, hero, find);

        if(node->right_son != nullptr)
            Find_node(node->right_son, hero, find);
    }
}

void Get_defenition(Tree *tree)
{
    assert(tree != nullptr);

    printf("Whose description do you want to get? Enter the name of this hero, honey)\n");

    char *hero = (char *)calloc(AKINATOR_SIZE, sizeof(char));

    Node *node = nullptr;

    while(true)
    {
        hero = Get_answer(hero);
        Find_node(tree->root, hero, &node);

        if(node == nullptr)
        {
            printf("Unfortunately, this hero isn't in the database. Dude, make a wish for someone else\n"
                   "Try again\n");
        }
        else
            break;
    }

    printf("Your hero ");

    while(true)
    {
        if(node->dad->dad == nullptr)
        {
            if(node->dad->left_son == node)
                printf("is %s.", node->dad->data);
            else
                printf("isn't %s.", node->dad->data);

            break;
        }

        if(node->dad->left_son == node)
            printf("is %s, ", node->dad->data);
        else
            printf("isn't %s, ", node->dad->data);

        node = node->dad;
    }
    free(hero);
}

void Get_comparison(Tree *tree)
{
    assert(tree != nullptr);

    printf("Whose comparison do you want to get? Enter the names of this heroes, honey)\n");

    char *hero1 = (char *)calloc(AKINATOR_SIZE, sizeof(char));
    char *hero2 = (char *)calloc(AKINATOR_SIZE, sizeof(char));

    Node *node1 = nullptr;
    Node *node2 = nullptr;

    printf("Enter the names of the first hero, my slave)\n");

    while(true)
    {
        hero1 = Get_answer(hero1);
        Find_node(tree->root, hero1, &node1);

        if(node1 == nullptr)
        {
            printf("Unfortunately, this hero isn't in the database. Dude, make a wish for someone else\n"
                   "Try again\n");
        }
        else
            break;
    }

    printf("Enter the names of the second hero, my slave)\n");

    while(true)
    {
        hero2 = Get_answer(hero2);
        Find_node(tree->root, hero2, &node2);

        if(node2 == nullptr)
        {
            printf("Unfortunately, this hero isn't in the database. Dude, make a wish for someone else\n"
                   "Try again\n");
        }
        else
            break;
    }

    while(true)
    {
        if(node1 != node2)
        {
            printf("%s ", hero1);

            if(node1->dad->left_son == node1)
                printf("is %s, ", node1->dad->data);
            else
                printf("isn't %s, ", node1->dad->data);

            printf("but %s", hero2);

            if(node2->dad->left_son == node2)
                printf(" is %s\n", node2->dad->data);
            else
                printf(" isn't %s\n", node2->dad->data);
        }
        else if(node1 == node2)
        {
            printf("%s and %s ", hero1, hero2);

            if(node2->dad->left_son == node2)
                printf("are %s.\n", node2->dad->data);
            else
                printf("aren't %s.\n", node2->dad->data);
        }

        if(node1->dad->dad == nullptr && node2->dad->dad == nullptr)
            break;
        else if(node1->dad->dad != nullptr && node2->dad->dad == nullptr)
        {
            while(true)
            {
                printf("%s ", hero1);

                node1 = node1->dad;

                if(node1->dad->left_son == node1)
                    printf(" is %s\n", node1->dad->data);
                else
                    printf(" isn't %s\n", node1->dad->data);

                if(node1->dad->dad == nullptr)
                    break;
            }
            break;
        }
        else if(node1->dad->dad == nullptr && node2->dad->dad != nullptr)
        {
            while(true)
            {
                printf("%s ", hero2);

                node2 = node2->dad;

                if(node2->dad->left_son == node2)
                    printf(" is %s\n", node2->dad->data);
                else
                    printf(" isn't %s\n", node2->dad->data);

                if(node2->dad->dad == nullptr)
                    break;
            }
            break;
        }
    node1 = node1->dad;
    node2 = node2->dad;
    }
}


















