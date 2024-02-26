#include <assert.h>
#include "skiplist.h"

/* 
 * Compilazione      make build/skiplist_unit_test
 * Esecuzione        build/skiplist_unit_test
 */

static SkipList *string_list;

void setUp() {
   string_list = create_skipList(precedes_node_string);
}

static void test_empty_skiplist(void){
   assert (NULL == (string_list->head)->next[0]);
}

static void test_one_node_skipList(void){ 
   insertSkipList(string_list, "Pietra");
   assert( searchSkipList(string_list, "Pietra") != NULL);
}

static void test_two_node_skipList(void) {
   insertSkipList(string_list, "vena");
   insertSkipList(string_list, "matita");
   assert((searchSkipList(string_list, "matita") != NULL) && (searchSkipList(string_list, "vena") != NULL));
}

static void test_skiplist_in_order(void) {
   int i, check = 0;
   Node *temp;
   char** strings_in_order = (char **)malloc(6*sizeof(char *));
   for(i=0; i<6; i++)
      strings_in_order[i] = (char *)malloc(10*sizeof(char));

   insertSkipList(string_list, "albero");
   insertSkipList(string_list, "pietra");
   insertSkipList(string_list, "cattedra");
   insertSkipList(string_list, "zoppo");
   insertSkipList(string_list, "zappo");
   insertSkipList(string_list, "anta");
   
   strings_in_order[0] = "albero";
   strings_in_order[1] = "anta";
   strings_in_order[2] = "cattedra";
   strings_in_order[3] = "pietra";
   strings_in_order[4] = "zappo";
   strings_in_order[5] = "zoppo";

   temp = string_list->head;
   i = 0;
   while(temp->next[0] != NULL) {
      check += strcasecmp(temp->next[0]->item, strings_in_order[i]);
      temp = temp->next[0];
      i++;
   }
   assert(check == 0);
}

int main(int argc, char const *argv[]) {
   setUp();
   test_empty_skiplist();
   printf("Test 1: done \n");
   skiplist_free_memory(string_list);
   setUp();
   test_one_node_skipList();
   printf("Test 2: done \n");
   skiplist_free_memory(string_list);
   setUp();
   test_two_node_skipList();
   printf("Test 3: done \n");
   skiplist_free_memory(string_list);
   setUp();
   test_skiplist_in_order();
   printf("Test 4: done \n");
   skiplist_free_memory(string_list);
   return 0;
}
