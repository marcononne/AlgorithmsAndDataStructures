#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <time.h>

/*
 * CASO D'USO:
 * > gcc -c orderedarray.c
 * > gcc -c orderedarray_precedences.c
 * > gcc orderedarray_main.c orderedarray.o orderedarray_precedences.o -o main
 * > ./main record.csv
 * > "Digitare il numero corrispondente al criterio di ordinamento scelto"
 * 
 * TESTS
 * > gcc -c orderedarray.c
 * > gcc -c orderedarray_precedences.c
 * > gcc orderedarray_unit_test.c orderedarray.o orderedarray_precedences.o -o tests
 * > ./tests
 */

struct _OrderedArray {
   void** array;
   int (*function)(void*, void*);
   int number_of_elements;
   int capacity;
};

typedef struct _OrderedArray OrderedArray;
/* This function creates an empty array and sets it sorting criteria 
 * with the given function; it returns the pointer to the orderedarray */
OrderedArray * array_create(int (*function)(void*, void*));
/* This function returns 1 (true) if the given orderedarray is empty
 * It returns 0 (false) otherwise. */
int array_is_empty(OrderedArray *);
/* This function returns the size of the given orderedarray */
int array_size(OrderedArray *);
/* This function adds the given element to the given orderedarray */
void array_add(OrderedArray *, void *);
/* This function returns the i-th element of the given orderedarray */
void* array_get(OrderedArray *, int);
/* This function frees the memory previously allocated for the given orderedarray */
void array_free_memory(OrderedArray *);
/* This function implements the quick sort algorithm;
 * it sorts the given orderedarray using the given integer indices */
void quick_sort(OrderedArray *, int, int);
/* This function implements a randomized quick sort algorithm;
 * it sorts the given orderedarray using the given integer indices */
void randomized_quick_sort(OrderedArray *, int, int);
/* This function implements a binary variant of the insertion sort algorithm 
 * it sorts the given orderedarray using the given integere indices */
void binary_insertion_sort(OrderedArray *, int, int);


