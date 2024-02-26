#include "orderedarray.h"

struct record {
    int identifier;
    char* string_field;
    int integer_field;
    double float_field;
};
// Function that implements the precedence relation between integers
int precedes_record_int_field(void* ,void* );

// Function that implements the precedence relation between strings
int precedes_record_string_field(void* ,void* );

// Function that implements the precedence relation between float
int precedes_record_float_field(void* , void* );
