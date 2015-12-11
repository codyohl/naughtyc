#ifndef N_STD_LIB_H
#define N_STD_LIB_H

#include <inttypes.h>

int32_t nstrlen(char* str);

char* nstr_new(char* input);

char* nstr_assign(char* input);

char* nstr_plus(char* s1, char* s2);

#endif //N_STD_LIB_H