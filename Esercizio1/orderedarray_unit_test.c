#include <assert.h>
#include "orderedarray_precedences.h"

static int check_records(void* r1_p, void* r2_p) {
    if(r1_p == NULL){
        fprintf(stderr,"precedes_record_int_field: the first parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_record_int_field: the second parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    int res = 1;
    struct record *rec1_p = (struct record*)r1_p;
    struct record *rec2_p = (struct record*)r2_p;
    if(rec1_p->integer_field == rec2_p->integer_field) {
        if( strcasecmp(rec1_p->string_field,rec2_p->string_field) == 0) {
            if(rec1_p->float_field != rec2_p->float_field)
                res = 0;
        } else
            res = 0;
    } else
        res = 0;

    return res;        
}
static OrderedArray *ordered_array_int;
static OrderedArray *ordered_array_float;
static OrderedArray *ordered_array_string;
static OrderedArray *expected_array;

void setUp(void) {
    ordered_array_int = array_create(precedes_record_int_field);
    ordered_array_float = array_create(precedes_record_float_field);
    ordered_array_string = array_create(precedes_record_string_field);
    expected_array = array_create(precedes_record_string_field);
}

void free_Memory(void) {
    array_free_memory(ordered_array_int);
    array_free_memory(ordered_array_string);
    array_free_memory(ordered_array_float);
    array_free_memory(expected_array);
}

static void test_integer_ordered_array_is_empty_zero_elements(void){
    assert(array_is_empty(ordered_array_int) == 1);
}

static void test_integer_ordered_array_is_empty_one_element(void){
    struct record *record_p = malloc(sizeof(struct record));
    record_p->identifier = 0;
    record_p->string_field = "Test1";
    record_p->integer_field = 102;
    record_p->float_field = 78.2;
    array_add(ordered_array_int, (void*)record_p);
    assert(array_is_empty(ordered_array_int) == 0);
}   

static void test_double_array_size_zero_elements(void){
    assert(array_size(ordered_array_float) == 0);
}

static void test_integer_array_size_two_el(void) {
    struct record *r1_p = malloc(sizeof(struct record));
    r1_p->identifier = 0;
    r1_p->string_field = "Casa";
    r1_p->integer_field = 46;
    r1_p->float_field = 8.923;
    array_add(ordered_array_int, (void*)r1_p);
    struct record *r2_p = malloc(sizeof(struct record));
    r2_p->identifier = 1;
    r2_p->string_field = "Appendino";
    r2_p->integer_field = 24;
    r2_p->float_field = 16.29;
    array_add(ordered_array_int, (void*)r2_p);
    assert(array_size(ordered_array_int) == 2);
}

static void test_string_array_add_ten_elements_QuickSort() {
    struct record *rec1_p = malloc(sizeof(struct record));
    rec1_p->identifier = 0;
    rec1_p->string_field = "Carlito's Way";
    rec1_p->integer_field = 99;
    rec1_p->float_field = 9.23;
    array_add(ordered_array_string, (void*)rec1_p);

    struct record *rec2_p = malloc(sizeof(struct record));
    rec2_p->identifier = 1;
    rec2_p->string_field = "Santeria";
    rec2_p->integer_field = 104;
    rec2_p->float_field = 1.04;
    array_add(ordered_array_string, (void*)rec2_p);
    
    struct record *rec3_p = malloc(sizeof(struct record));
    rec3_p->identifier = 2;
    rec3_p->string_field = "Bastavano le briciole";
    rec3_p->integer_field = 802;
    rec3_p->float_field = 80.2;
    array_add(ordered_array_string, (void*)rec3_p);

    struct record *rec4_p = malloc(sizeof(struct record));
    rec4_p->identifier = 3;
    rec4_p->string_field = "In Radio";
    rec4_p->integer_field = 1;
    rec4_p->float_field = 0.0001;
    array_add(ordered_array_string, (void*)rec4_p);
    
    struct record *rec5_p = malloc(sizeof(struct record));
    rec5_p->identifier = 4;
    rec5_p->string_field = "Salvador Dalì";
    rec5_p->integer_field = 62;
    rec5_p->float_field = 0.62;
    array_add(ordered_array_string, (void*)rec5_p);

    struct record *rec6_p = malloc(sizeof(struct record));
    rec6_p->identifier = 5;
    rec6_p->string_field = "Marracash";
    rec6_p->integer_field = 93;
    rec6_p->float_field = 93.01;
    array_add(ordered_array_string, (void*)rec6_p);

    struct record *rec7_p = malloc(sizeof(struct record));
    rec7_p->identifier = 6;
    rec7_p->string_field = "Scooteroni";
    rec7_p->integer_field = 42;
    rec7_p->float_field = 4.2;
    array_add(ordered_array_string, (void*)rec7_p);

    struct record *rec8_p = malloc(sizeof(struct record));
    rec8_p->identifier = 7;
    rec8_p->string_field = "Quasi Amici";
    rec8_p->integer_field = 13;
    rec8_p->float_field = 1.3;
    array_add(ordered_array_string, (void*)rec8_p);
    
    struct record *rec9_p = malloc(sizeof(struct record));
    rec9_p->identifier = 8;
    rec9_p->string_field = "Insta Lova";
    rec9_p->integer_field = 16;
    rec9_p->float_field = 1.666;
    array_add(ordered_array_string, (void*)rec9_p);

    struct record *rec10_p = malloc(sizeof(struct record));
    rec10_p->identifier = 9;
    rec10_p->string_field = "Crudelia";
    rec10_p->integer_field = 9;
    rec10_p->float_field = 0.0099;
    array_add(ordered_array_string, (void*)rec10_p);

    quick_sort(ordered_array_string, 0, array_size(ordered_array_string)-1);
    
    array_add(expected_array,(void*)rec3_p);
    array_add(expected_array,(void*)rec1_p);
    array_add(expected_array,(void*)rec10_p);
    array_add(expected_array,(void*)rec4_p);
    array_add(expected_array,(void*)rec9_p);
    array_add(expected_array,(void*)rec6_p);
    array_add(expected_array,(void*)rec8_p);
    array_add(expected_array,(void*)rec5_p);
    array_add(expected_array,(void*)rec2_p);
    array_add(expected_array,(void*)rec7_p);

    int res = 1, i = 0;
    while (res && i < 10) {
        res = check_records( array_get(ordered_array_string, i) , array_get(expected_array, i) );
        i++;
    }
    assert(res == 1);
}

static void test_string_array_add_ten_elements_BinaryInsertionSort() {
    
    struct record *rec1_p = malloc(sizeof(struct record));
    rec1_p->identifier = 0;
    rec1_p->string_field = "Carlito's Way";
    rec1_p->integer_field = 99;
    rec1_p->float_field = 9.23;
    array_add(ordered_array_string, (void*)rec1_p);

    struct record *rec2_p = malloc(sizeof(struct record));
    rec2_p->identifier = 1;
    rec2_p->string_field = "Santeria";
    rec2_p->integer_field = 104;
    rec2_p->float_field = 1.04;
    array_add(ordered_array_string, (void*)rec2_p);
    
    struct record *rec3_p = malloc(sizeof(struct record));
    rec3_p->identifier = 2;
    rec3_p->string_field = "Bastavano le briciole";
    rec3_p->integer_field = 802;
    rec3_p->float_field = 80.2;
    array_add(ordered_array_string, (void*)rec3_p);

    struct record *rec4_p = malloc(sizeof(struct record));
    rec4_p->identifier = 3;
    rec4_p->string_field = "In Radio";
    rec4_p->integer_field = 1;
    rec4_p->float_field = 0.0001;
    array_add(ordered_array_string, (void*)rec4_p);
    
    struct record *rec5_p = malloc(sizeof(struct record));
    rec5_p->identifier = 4;
    rec5_p->string_field = "Salvador Dalì";
    rec5_p->integer_field = 62;
    rec5_p->float_field = 0.62;
    array_add(ordered_array_string, (void*)rec5_p);

    struct record *rec6_p = malloc(sizeof(struct record));
    rec6_p->identifier = 5;
    rec6_p->string_field = "Marracash";
    rec6_p->integer_field = 93;
    rec6_p->float_field = 93.01;
    array_add(ordered_array_string, (void*)rec6_p);

    struct record *rec7_p = malloc(sizeof(struct record));
    rec7_p->identifier = 6;
    rec7_p->string_field = "Scooteroni";
    rec7_p->integer_field = 42;
    rec7_p->float_field = 4.2;
    array_add(ordered_array_string, (void*)rec7_p);

    struct record *rec8_p = malloc(sizeof(struct record));
    rec8_p->identifier = 7;
    rec8_p->string_field = "Quasi Amici";
    rec8_p->integer_field = 13;
    rec8_p->float_field = 1.3;
    array_add(ordered_array_string, (void*)rec8_p);
    
    struct record *rec9_p = malloc(sizeof(struct record));
    rec9_p->identifier = 8;
    rec9_p->string_field = "Insta Lova";
    rec9_p->integer_field = 16;
    rec9_p->float_field = 1.666;
    array_add(ordered_array_string, (void*)rec9_p);

    struct record *rec10_p = malloc(sizeof(struct record));
    rec10_p->identifier = 9;
    rec10_p->string_field = "Crudelia";
    rec10_p->integer_field = 9;
    rec10_p->float_field = 0.0099;
    array_add(ordered_array_string, (void*)rec10_p);
    
    binary_insertion_sort(ordered_array_string, 0, array_size(ordered_array_string)-1);

    array_add(expected_array,(void*)rec3_p);
    array_add(expected_array,(void*)rec1_p);
    array_add(expected_array,(void*)rec10_p);
    array_add(expected_array,(void*)rec4_p);
    array_add(expected_array,(void*)rec9_p);
    array_add(expected_array,(void*)rec6_p);
    array_add(expected_array,(void*)rec8_p);
    array_add(expected_array,(void*)rec5_p);
    array_add(expected_array,(void*)rec2_p);
    array_add(expected_array,(void*)rec7_p);

    

    int res = 1, i = 0;
    while (res && i < 10) {
        res = check_records( array_get(ordered_array_string, i) , array_get(expected_array, i) );
         i++;
    }
    assert(res == 1);
}
int main(int argc, char** argv) {
    setUp();
    test_integer_ordered_array_is_empty_zero_elements();
    free_Memory();
    setUp();
    test_integer_ordered_array_is_empty_one_element();
    free_Memory();
    setUp();
    test_double_array_size_zero_elements();
    free_Memory();
    setUp();
    test_integer_array_size_two_el();
    free_Memory();
    setUp();
    test_string_array_add_ten_elements_QuickSort();
    free_Memory();
    setUp();
    test_string_array_add_ten_elements_BinaryInsertionSort();
    free_Memory();
}
