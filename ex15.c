#include <stdio.h>

int main(int argc, char *argv[])
{
  int ages[] = {11, 12, 13, 14};
  char *names[] = {
    "Alan", "Frank", "Mary", "John"
  };

  int count = sizeof(ages) / sizeof(int);

  // first way using indices
  for(int i = 0; i < count; i++) {
    printf("%s has %d years alive.\n", names[i], ages[i]);
  }

  printf("---\n");

  // setup the pointers to the start of the arrays
  int * cur_age = ages;
  char * * cur_name = names;

  // second way using pointers
  for(int i = 0; i < count; i++){
    printf("%s i %d years old\n", *(cur_name + i), *(cur_age + i));
  }

  printf("---\n");

  // third way using pointers in a stupid complex way
  for(cur_name = names, cur_age = ages;
      (cur_age - ages) < count;
      cur_name++, cur_age++)
  {
    printf("%s lived %d years so far.\n", *cur_name, *cur_age);
  }

  return 0;
}
