#include<stdio.h>

int main(){

  int array[5] = {10,20,30,40,50};
  int angka[10];
  float nilai[5] = {0.0};
  char nama [30] = "arfy";

  int *pointer = array ; 
  for(int i = 0; i<5 ; i++){
    printf ("array %d = %d \n", i, array[i]);
  }
  printf("array %p \n", (void*) array);
  printf ("&array %p \n", &array);
  printf("sizeof dari array : %zu\n", sizeof(array)); // 5x4
  printf("sizeof dari pointer : %zu\n", sizeof(pointer));

  return 0;
}