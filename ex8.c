#include <stdio.h>

int main(int argc, char *argv[])
{
  volatile int areas[] = {10, 12, 13, 14, 20};
  volatile char name [] = "Zed";
  volatile char full_name[] = {
    'Z', 'e', 'd', ' ', 'A', '.', '\n'
  };

  printf("Size of an int %ld\n", sizeof(int));
  printf("Size of int[] areas %ld\n", sizeof(areas));
  printf("Size of char %ld\n", sizeof(char));
  printf("Size of char[] name %ld\n", sizeof(name));
  printf("Size of char[] full_name %ld\n", sizeof(name));
  printf("Full name: %s", full_name);

  return 0;
}
