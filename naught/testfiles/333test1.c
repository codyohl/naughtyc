#include <stdio.h>
#include <stdlib.h>
#include <nstdlib.h>
#include <inttypes.h>


int32_t fact(int32_t x, int* p);
int32_t main(int32_t argc, char* arg) {
  pointer p;
  int32_t temp0 = fact(3, p);
  printf("",  temp0);
    
}
int32_t fact(int32_t x, int* p) {
  int32_t temp1;
  if (x) {
    int32_t temp1 = x-1;
    int32_t temp2 = fact(temp1, p);
    int32_t temp3 = x* temp2;
     temp1 = temp3;
  } else { 
     temp1 = 1;
  }
  *(p) = temp1;
  return *(p);
  
}
int32_t fact2(int32_t x, int* p) {
  int32_t e;

  e = *(p);
    
  *(p) = 54;
    
  int* temp5 = &(*(p))
  p = temp5;
    
}

