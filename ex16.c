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

struct Person * // return type "pointer to struct-Person"
Person_create(char *name, int age, int height, int weight)
{
  // allocate memory for a struct-person
  // (malloc returnes the memory address)
  // store the address in who pointer
  struct Person * who = malloc(sizeof(struct Person));

  // assert, that we could indeed allocate memory
  assert(who != NULL);

  // string duplication from string.h
  // we allocate new memory here, again
  // stdup returns address of copied string (type char*)
  // who->name = strdup(name)
  // This gives compile time warnings, since it not standard C (99)
  // => Use explicit memory allocation and strcpy
  who->name = malloc(strlen(name)+1);
  strcpy(who->name, name);

  // copy remaining values
  who->age  = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void
Person_destroy(struct Person * who)
{
  assert(who != NULL); // not the NULL pointer? not allocated?

  free(who->name); // give back memory allocated for name
  free(who); // give back memory allocated for who
}

void
Person_print(struct Person * who)
{
  printf("Person %s: [age: %d, ht: %d, tw: %d]\n", who->name, who->age,  who->height, who->weight);
}

int
main(int argc, char *argv[]){
  // make joe Person
  struct Person *joe = Person_create("Joe", 32, 64, 140);

  Person_print(joe);

  Person_destroy(joe);

  return 0;
}
