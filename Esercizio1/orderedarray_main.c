#include "orderedarray_precedences.h"

#define STOP 5000000

// Function that reads from input file
static void load_array(const char* file_path, OrderedArray* ordered_array){
    char *read_line_p;
    char buffer[1024];
    int buf_size = 1024, cont=0;
    FILE *fp;
    printf("\nLoading data from file...");
    fp = fopen(file_path,"r");
    if(fp == NULL){
        fprintf(stderr,"main: unable to open the file %s\n",file_path);
        exit(EXIT_FAILURE);
    }
    while(fgets(buffer,buf_size,fp) != NULL && cont<STOP){  
        read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
        if(read_line_p == NULL){
            fprintf(stderr,"main: unable to allocate memory for the read line");
            exit(EXIT_FAILURE);
        }   
        strcpy(read_line_p,buffer);  
        char *identifier_in_read_line_p = strtok(read_line_p, ","); 
        char *string_field_in_read_line_p = strtok(NULL,",");
        char *integer_field_in_read_line_p = strtok(NULL,",");  
        char *float_field_in_read_line_p = strtok(NULL,",");
        char *string_field = malloc((strlen(string_field_in_read_line_p)+1)*sizeof(char));
        if(string_field == NULL){
            fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
            exit(EXIT_FAILURE);
        }  
        strcpy(string_field,string_field_in_read_line_p);
        int id = atoi(identifier_in_read_line_p);
        int integer_field = atoi(integer_field_in_read_line_p); 
        double float_field = atof(float_field_in_read_line_p);
        struct record *record_p = malloc(sizeof(struct record));
        if(record_p == NULL){
            fprintf(stderr,"main: unable to allocate memory for the read record");
            exit(EXIT_FAILURE);
        }
        record_p->identifier = id;
        record_p->string_field = string_field;
        record_p->integer_field = integer_field;
        record_p->float_field = float_field;
        array_add(ordered_array, (void*)record_p);
        free(read_line_p);
        cont++;
    }   
    fclose(fp);
    printf("DONE\n");
}

static void free_array(OrderedArray* ordered_array){
    int el_num = array_size(ordered_array);
    for(int i = 0;i<el_num;i++){
        struct record *array_element =(struct record *) array_get(ordered_array, i);
        free(array_element->string_field);
        free(array_element);
    }
    array_free_memory(ordered_array);
}

void print_array(OrderedArray* ordered_array){
    int el_num = array_size(ordered_array);
    struct record *array_element;

    printf("\nORDERED ARRAY OF RECORDS\n");
    for(int i = 0;i<el_num;i++){
        array_element = (struct record *)array_get(ordered_array, i);
        printf("<%d, %s , %d , %lf>\n", array_element->identifier, array_element->string_field, array_element->integer_field, array_element->float_field);
    }
}

// This function creates and empty ordered array using 'array_create', then calls the function
// 'load_array' to load the array. Now it calls the function 'merge_sort' to sort the array,
// the fourth parameter is 'k', the parameter that we use to decide, depending on the size
// of the array, if we have to use Merge Sort or Insertion Sort to sort the array.
static void test_with_comparison_function(const char* file_path, int choice, int (*compare)(void*,void*)){
   OrderedArray* ordered_array = array_create(compare);
   load_array(file_path, ordered_array);
   if(choice == 1) {
      printf("SORTING WITH QUICK-SORT \n");
      quick_sort(ordered_array, 0, array_size(ordered_array)-1);
   } 
   else {
       if(choice == 2) {
            printf("SORTING WITH RANDOMIZED-QUICK-SORT \n");
            randomized_quick_sort(ordered_array, 0, array_size(ordered_array)-1);
       } else {
            printf("SORTING WITH BINARY-INSERTION-SORT \n");
            binary_insertion_sort(ordered_array, 0, array_size(ordered_array)-1);
       }
   }
   free_array(ordered_array);
}

int main(int argc, char const *argv[]){
    if(argc < 2){
        printf("Usage: ordered_array_main <path_to_data_file>\n");
        exit(EXIT_FAILURE);
    }
    int check = 0, choice = 0;
    do {
       printf("1 - Order with Quick-Sort \n2 - Order with Randomized-Quick-Sort \n3 - Order with Binary-Insertion-Sort\n");
       scanf("%d", &choice);
       check = (choice == 1 || choice == 2 || choice == 3);
    } while (check == 0);
   
   clock_t begin = clock();
   test_with_comparison_function(argv[1], choice, precedes_record_int_field);
   clock_t end = clock();
   double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
   printf("Time spent sorting the ordered_array with integers: %lf \n", time_spent);

   begin = clock();
   test_with_comparison_function(argv[1], choice, precedes_record_float_field);
   end = clock();
   time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
   printf("Time spent sorting the ordered_array with floating point numbers: %lf\n", time_spent);

   begin = clock();
   test_with_comparison_function(argv[1], choice, precedes_record_string_field);
   end = clock();
   time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
   printf("Time spent sorting the ordered_array with strings: %lf\n", time_spent);

    return (EXIT_SUCCESS);
}
