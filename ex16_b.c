#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person { // declares type "struct-Person"
  char * name;
  int age;
  int height;
  int weight;
};

void
Person_print(struct Person who)
{
  printf("Person %s: [age: %d, ht: %d, tw: %d]\n", who.name, who.age,  who.height, who.weight);
}

int
main(int argc, char *argv[]){
  // make joe Person
  struct Person joe;
  joe.name = "Joe";
  joe.age = 22;
  joe.height = 3;
  joe.weight = 4;

  Person_print(joe);
  return 0;
}
