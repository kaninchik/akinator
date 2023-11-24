#ifndef AKINATOR_H
#define AKINATOR_H

#include <cstdio>
#include "tree.h"

const int AKINATOR_SIZE = 50;

size_t Get_file_size(FILE *fp);
char *Get_file_content();
bool Get_string(Node **node, char **buffer);
void Fucking_filling_function(Tree *tree, Node **node, Node *dad, char **buffer);
void Guess_object(Tree *tree);
char *Get_answer(char *answer);
void Find_node(Node *node, char *hero, Node **find);
void Get_defenition(Tree *tree);
void Get_comparison(Tree *tree);

#endif
