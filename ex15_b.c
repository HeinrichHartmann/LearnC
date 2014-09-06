#include <stdio.h>

int main(int argc, char *argv[])
{
  volatile int ages[] = {11, 12, 13, 14};
  volatile char one_name[] = "Lena";
  volatile char * one_name_ptr = "Lena";
  volatile char one_name_arr[] = {'a','b','c', 0};
  volatile char * one_name_arr_ptr = one_name_arr;
  volatile char *names[] = {
    "Alan", "Frank", "Mary", "John"
  };

  char * * cur_name = names;
  printf("Value of cur_names pointer: %p\n", cur_name);
  printf("Value of * cur_names pointer: %p\n", * cur_name);
  printf("Value of * * cur_names char: %c\n", * * cur_name);

  printf("---\n");
  printf("Value of one_name[]: %s\n", one_name);
  printf("Value of one_name_ptr: %s\n", one_name_ptr);
  printf("Value of one_name_arr: %s\n", one_name_arr);
  printf("Value of one_name_arr_ptr: %s\n", one_name_arr_ptr);

  for(int i=0; i < 5; i++){
    printf("ages + %d as int-pointer: %d\n", i, *((int*) (* cur_name) + i));
  }

  return 0;
}
