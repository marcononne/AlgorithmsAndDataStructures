#include "skiplist.h"

static void adapt_head_size(SkipList *list, int newSize);

int precedes_node_string(void* item1, void* item2) {
   if(item1 == NULL){
      fprintf(stderr,"precedes_string: the first parameter cannot be NULL \n");
      exit(EXIT_FAILURE);
   }
   if(item2 == NULL){
      fprintf(stderr,"precedes_string: the second parameter cannot be NULL \n");
      exit(EXIT_FAILURE);
   }
   char *word1 = (char *)item1;
   char *word2 = (char *)item2;
    if (strcasecmp(word1, word2) < 0)
      return 1;

   return 0;
}

Node * create_node(void* item, int size) {
    if(item == NULL) {
        fprintf(stderr, "An error occurred in create_node: first parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    if(size < 0) {
        fprintf(stderr, "An error occurred in create_node: second parameter cannot be negative \n");
        exit(EXIT_FAILURE);
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if(node == NULL) {
        fprintf(stderr, "An error occurred in create_node: unable to allocate memory for the Node \n");
        exit(EXIT_FAILURE);
    }

    node->next = (Node **)malloc(size * sizeof(Node *));
    node->item = item;
    node->size = size;

    return node;
}

SkipList * create_skipList(int (*precedes)(void* it_1, void* it_2)) {
    if(precedes == NULL) {
        fprintf(stderr, "An error occured in create_skipList: parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }

    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    if(list == NULL) {
        fprintf(stderr, "An error occurred in create_skipList: unable to allocate memory for the SkipList \n");
        exit(EXIT_FAILURE);
    }

    Node *h = create_node("head", 1);

    list->head = h;
    list->max_level = 0;
    list->compare = precedes;
    
    return list;
}

void skiplist_free_memory(SkipList *list) {
    Node *temp;
    while(list->head != NULL) {
        temp = list->head;
        list->head = (list->head)->next[0];
        free(temp);
    }
    free(list);
}

int randomLevel() {
    int lvl = 1;
    int r = ( random() % MAX_HEIGHT );
    while (r < (MAX_HEIGHT/2) && lvl < MAX_HEIGHT) {
        lvl++;
        r = ( random() % MAX_HEIGHT );
    }
    return lvl;
}

void insertSkipList(SkipList *list, void* item) {
    if(list == NULL) {
        fprintf(stderr, "An error occurred in insertSkipList: first parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    if(item == NULL) {
        fprintf(stderr, "An error occurred in insertSkipList: second parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    int sizeN = randomLevel();
    Node *newNode = create_node(item, sizeN);
    if(newNode->size > list->max_level) {
        adapt_head_size(list, newNode->size);
    }
    Node *temp = list->head;
    for(int k = list->max_level-1; k >= 0; k--) {
        if(temp->next[k] == NULL || (*(list)->compare)(item, (temp->next[k])->item)) {
            if(k < newNode->size) {
                newNode->next[k] = temp->next[k];
                temp->next[k] = newNode;
            }
        } else {
            temp = temp->next[k];
            k++;
        }
    }
}

/* Every time a new node is going to be insert into the SkipList, it might be needed to adapt the head size:
 * if the new node has a greater size than the actual head's size, it's mandatory to adapt the head size to a new value */
static void adapt_head_size(SkipList *list, int newSize) {
    /* A new node is created and it will become the head of the skiplist; 
     * the node is created with an updated size */
    Node *newHead = create_node("head", newSize);
    Node *prevHead;
    int k = 0;

    /* Adapting the pointers to the following elements in the skiplist */
    while(k < newSize) {
        if(k < list->max_level) {
            newHead->next[k] = (list->head)->next[k];
        }
        else {
            newHead->next[k] = NULL;
        }
        k++;
    }

    list->max_level = newSize;
    prevHead = list->head;
    list->head = newHead;
    free(prevHead);
}

void* searchSkipList(SkipList *list, void* item) {
    if(list == NULL) {
        fprintf(stderr, "An error occurred in insertSkipList: first parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    if(item == NULL) {
        fprintf(stderr, "An error occurred in insertSkipList: second parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }

    Node *temp = list->head;
    int i;
    for(i = list->max_level-1; i >= 0; i--) {
        while(temp->next[i] != NULL && (*(list)->compare)((temp->next[i])->item, item) ) {
            temp = temp->next[i];
        }
    }
    if( (*(list)->compare)((temp->next[i+1])->item, item) == 0 && (*(list)->compare)(item,(temp->next[i+1])->item) == 0) {
        return item;
    }
    else
        return NULL;
}
