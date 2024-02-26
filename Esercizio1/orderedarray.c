#include "orderedarray.h"
#define INITIAL_CAPACITY 2

static int binary_find_index_to_insert(OrderedArray *, void*, int, int);
static int partition(OrderedArray *, int, int);
static int randomized_partition(OrderedArray *, int, int);

OrderedArray * array_create(int (*function)(void*, void*)) {
  if(function == NULL) {
    fprintf(stderr, "An error occurred in array_create: function parameter cannot be NULL \n");
    exit(EXIT_FAILURE);
  }
  OrderedArray *ordered_array = (OrderedArray *)malloc(sizeof(OrderedArray));
  if(ordered_array == NULL) {
    fprintf(stderr, "An error occurred in array_create: unable to allocate memory for the ordered array");
    exit(EXIT_FAILURE);
  }
  ordered_array->array = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
  if(ordered_array->array == NULL) {
    fprintf(stderr, "An error occurred in array_create: unable to allocate memory for the interal array");
    exit(EXIT_FAILURE);
  }
  ordered_array->number_of_elements = 0;
  ordered_array->capacity = INITIAL_CAPACITY;
  ordered_array->function = function;

  return(ordered_array);
}

int array_is_empty(OrderedArray *ordered_array) {
  if(ordered_array == NULL) {
    fprintf(stderr, "An error occurred in array_is_empty: parameter cannot be NULL \n");
    exit(EXIT_FAILURE);
  }
  if(ordered_array->number_of_elements == 0)
    return 1;

  return 0;
}

int array_size(OrderedArray *ordered_array) {
  if(ordered_array == NULL) {
    fprintf(stderr, "An error occurred in array_size: parameter cannot be NULL \n");
    exit(EXIT_FAILURE);
  }
  return ordered_array->number_of_elements;
}

void array_add(OrderedArray *ordered_array, void* element) {
  if(ordered_array == NULL) {
    fprintf(stderr, "An error occurred in array_add_element: parameter 'ordered_array' cannot be NULL \n");
    exit(EXIT_FAILURE);
  }
  if(element == NULL) {
    fprintf(stderr, "An error occurred in array_add_element: parameter 'element' cannot be NULL \n");
    exit(EXIT_FAILURE);
  }
  if(ordered_array->number_of_elements >= ordered_array->capacity) {
    ordered_array->array = (void**)realloc(ordered_array->array, 2*((unsigned long)ordered_array->capacity)*sizeof(void*));
    if(ordered_array->array == NULL) {
      fprintf(stderr, "An error occurred in array_add_element: unable to reallocate memory for the internal array");
      exit(EXIT_FAILURE);
    }
    ordered_array->capacity = 2*ordered_array->capacity;
  }
  (ordered_array->array)[ordered_array->number_of_elements] = element;
  ordered_array->number_of_elements++;
}

void* array_get(OrderedArray *ordered_array, int i) {
  if(ordered_array == NULL) {
    fprintf(stderr, "An error occurred in array_get: parameter 'ordered_array' cannot be NULL \n");
    exit(EXIT_FAILURE);
  }
  if(i<0 || i >= ordered_array->number_of_elements) {
    fprintf(stderr, "An error occurred in array_size: parameter 'i' is out of the array bounds");
    exit(EXIT_FAILURE);
  }
  return (ordered_array->array)[i];
}

void array_free_memory(OrderedArray *ordered_array){
  if(ordered_array == NULL){
    fprintf(stderr,"An error occurred in array_free_memory: parameter cannot be NULL \n");
    exit(EXIT_FAILURE);
  }
  free(ordered_array->array);
  free(ordered_array);
}

void quick_sort(OrderedArray * ordered_array, int left, int right) {
  if(left < right) {
    int my_partition = partition(ordered_array, left, right);
    quick_sort(ordered_array, left, my_partition-1);
    quick_sort(ordered_array, my_partition+1, right);
  }
}

void randomized_quick_sort(OrderedArray * ordered_array, int left, int right) {
  if(left < right) {
    int my_partition = randomized_partition(ordered_array, left, right);
    quick_sort(ordered_array, left, my_partition-1);
    quick_sort(ordered_array, my_partition+1, right);
  }
}

static int randomized_partition(OrderedArray * ordered_array, int left, int right) {
  int i = ( rand() % ( (right - left) + 1 ) + left);
  void* temp = (ordered_array->array)[i];
  (ordered_array->array)[i] = (ordered_array->array)[right];
  (ordered_array->array)[right] = temp;
  return partition(ordered_array, left, right);
}

static int partition(OrderedArray * ordered_array, int left, int right) {
  void* temp;
  void* pivot;
  int i, j;

  pivot = (ordered_array->array)[right];
  i = left - 1;
  for(j = left; j < right; j++) {
    if( ( *(ordered_array->function))( (ordered_array->array)[j], pivot) ) {
      i++;
      temp = (ordered_array->array)[i];
      (ordered_array->array)[i] = (ordered_array->array)[j];
      (ordered_array->array)[j] = temp;
    }
  }
  temp = (ordered_array->array)[i + 1];
  (ordered_array->array)[i + 1] = (ordered_array->array)[right];
  (ordered_array->array)[right] = temp;

  return i + 1;
}

void binary_insertion_sort(OrderedArray * ordered_array, int left, int right) {
  int i, j, pos;
  void* selected;

  for(i = left; i <= right; i++) {
    j = i - 1;
    selected = (ordered_array->array)[i];
    pos = binary_find_index_to_insert(ordered_array, selected, 0, j);
    while(j>=pos) {
      (ordered_array->array)[j+1] = (ordered_array->array)[j];
      j--;
    }
    (ordered_array->array)[j+1] = selected;
  }
}

static int binary_find_index_to_insert(OrderedArray * ordered_array, void* element, int left, int right) {
  if (right<=left) 
    return ( (*(ordered_array->function)) ( element, ( (ordered_array->array)[left]) ) ) ? left : (left+1);

  int middle = (int) ((left+right)/2);

  if( ((*(ordered_array->function)) ( element , ( (ordered_array->array)[middle]) ) ) && ( (*(ordered_array->function)) (( (ordered_array->array)[middle]), element) ) )
    return (middle + 1);

  if( !((*(ordered_array->function)) ( element , ( (ordered_array->array)[middle]) ) ))
    return binary_find_index_to_insert(ordered_array, element, middle+1, right);

  return binary_find_index_to_insert(ordered_array, element, left, middle-1);
}
