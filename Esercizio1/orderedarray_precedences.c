#include "orderedarray_precedences.h"
// Function that implements the precedence relation between integers

int precedes_record_int_field(void* r1_p,void* r2_p){
    if(r1_p == NULL){
        fprintf(stderr,"precedes_record_int_field: the first parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_record_int_field: the second parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    struct record *rec1_p = (struct record*)r1_p;
    struct record *rec2_p = (struct record*)r2_p;
    if(rec1_p->integer_field <= rec2_p->integer_field){
        return(1);
    }
    return(0);
}

// Function that implements the precedence relation between strings
int precedes_record_string_field(void* r1_p,void* r2_p){
    if(r1_p == NULL){
        fprintf(stderr,"precedes_string: the first parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_string: the second parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    struct record *rec1_p = (struct record*)r1_p;
    struct record *rec2_p = (struct record*)r2_p;
    if (strcmp(rec1_p->string_field,rec2_p->string_field) <= 0){
        return(1);
    }
    return(0);
}

// Function that implements the precedence relation between float
int precedes_record_float_field(void* r1_p, void* r2_p) {
    if(r1_p == NULL){
        fprintf(stderr,"precedes_float: the first parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_float: the second parameter cannot be NULL \n");
        exit(EXIT_FAILURE);
    }
    struct record *rec1_p = (struct record*)r1_p;
    struct record *rec2_p = (struct record*)r2_p;
    if (rec1_p->float_field <= rec2_p->float_field){
        return(1);
    }
    return(0);
}
