#ifndef AKINATOR_H
#define AKINATOR_H

#include <cstdio>
#include "tree.h"

const int AKINATOR_SIZE = 50;

size_t Get_file_size(FILE *fp);
char *Get_file_content();
void Get_string(Node **node, char **buffer);
void Fucking_filling_function(Node **node, char **buffer);
void Guess_object(Tree *tree);
char *Get_answer(char *answer);

#endif
