#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*
concat(const char *f, const char *g){
  char *o = malloc(sizeof(char) * (strlen(f) + strlen(g) + 1));
  strcpy(o,f);
  strcat(o,g);
  return o;
}

int main(){

  char * s = "Hello ";
  char * t = "World!";

  printf("%s\n", s);
  printf("%s\n", t);

  char * o = concat(s,t);

  printf("%s\n",);

  free(o);

  return 0;
}

