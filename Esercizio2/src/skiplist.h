#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

#define MAX_HEIGHT 10000

typedef struct _SkipList SkipList;
typedef struct _Node Node;

struct _SkipList {
  Node *head;
  int max_level;  // determines the current maximum among the various sizes of the Nodes in the SkipList
  int (*compare)(void*, void*);
};

struct _Node {
  Node **next;
  int size; // number of pointers in a given node of the skiplist
  void *item;
};

/* This function creates a node setting its key (first parameter) and 
 * the size of its array of pointers to the following elements (second parameter); 
 * it returns the pointer to the Node */
Node * create_node(void *, int);
/* This function creates an empty skiplist and sets its sorting criteria with the given function;
 * it returns the pointer to the SkipList*/
SkipList * create_skipList(int (*function)(void*, void*));
/* This function insert the given item (second parameter) into the given Skiplist (second parameter) */
void insertSkipList(SkipList *, void *);
/* This function returns a random integer that will be used to establish the size of the array of pointer of a Node */
int randomLevel();
/* This function searches for the given element (first parameter) in the given Skiplist (second parameter);
 * it returns the element if found; NULL otherwise */
void* searchSkipList(SkipList *, void *);
/* This function frees the memory previously allocated for the given SkipList */
void skiplist_free_memory(SkipList *);

int precedes_node_string(void* item1, void* item2);
