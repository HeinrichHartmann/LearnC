#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void
die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

// create a fake type "compare_cb" for a function pointer
typedef int (*compare_cb) (int a, int b);


/**
 * A classc bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *
bubble_sort(int *numbers, int count, compare_cb cmp)
{
  int temp = 0;
  int i = 0;
  int j = 0;
  int *target = malloc(count * sizeof(int));

  memcpy(target, numbers, count * sizeof(int));

  for(i = 0; i < count; i++) {
    for(j = 0; j < count - 1; j++) {
      if (cmp(target[j], target[j+1]) > 0) {
	// swap target[j], target[j+1]
	temp = target[j+1];
	target[j+1] = target[j];
	target[j] = temp;
      }
    }
  }

  return target;
}

/// SORT FUNCTIONS ///
int sorted_order(int a, int b) { return b - a; }
int reverse_order(int a, int b) { return a - b; }

void
print_numbers(int * numbers, int count)
{
  for(int i = 0; i < count; i++){
    printf("%d ", *(numbers+i));
  }
  printf("\n");
}

int
main(int argc, char * argv[])
{
  if (argc < 2) die("USAGE: ex18 13 11 9");

  int count = argc - 1;
  char ** inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  if(! numbers) die("Memory error");

  for(int i=0; i < count; i++){
    numbers[i] = atoi(inputs[i]);
  }

  print_numbers(numbers, count);

  int * sorted = bubble_sort(numbers, count, sorted_order);

  print_numbers(sorted, count);

  free(sorted);

  free(numbers);
}
