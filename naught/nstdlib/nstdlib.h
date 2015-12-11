#ifndef N_STD_LIB_H
#define N_STD_LIB_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct nstring_st {
  int32_t    len;     // The length of the string, ignoring the trailing \0
  char       str[];   // This is a C-style string
} nstring_st;

uint32_t nstrlen(char * string);

char * nstr_new(char * input);

char * nstr_assign(char * input);

char * nstr_plus(char * s1, char * s2);

#endif N_STD_LIB_H