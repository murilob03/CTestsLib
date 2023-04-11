#ifndef ARRAY_LIST_H_INCLUDED
#define ARRAY_LIST_H_INCLUDED

/*
This interface defines a List to store array tests.

*******This interface was designed for specifc use*******
*/

/* Exported type */
typedef struct ArrayList TArrList;
typedef struct ArrayTest TArrTest;

/* Define a struct to encapsulate functions */
struct arrayTestsList
{
    /*@brief Creates a new list and returns a pointer to it.*/
    TArrList* (*new_list)();
    /*@brief Add a test in the beginning of the list */
    void (*add)(TArrList *list, void* expect, void* test, 
                 int expected_size, int test_size, int d_type, int line);
    /*@brief Returns a pointer to the first test 
    and remove it from the list, returns NULL if 
    the list is empty.*/
    TArrTest* (*pop)(TArrList* list);
};

/* Declare a global struct */
extern struct arrayTestsList ArrayTestsList;

TArrList* __new_array_list();

void __add_array_test(TArrList *list, void* expect, void* test, 
                 int expected_size, int test_size, int d_type, int line);

TArrTest* __pop_array(TArrList *list);

#endif
