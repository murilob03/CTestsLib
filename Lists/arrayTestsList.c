#include <stdio.h>
#include <stdlib.h>
#include "arrayTestsList.h"

typedef struct ArrayTest *p_arr_test;

struct ArrayTest
{
    void* expected;
    void* to_test;
    int expected_size;
    int to_test_size;
    int type;
    TArrTest *next;
    int line;
};

struct ArrayList
{
    p_arr_test head;
    int qtt;
};

/*@brief Creates a list and returns a pointer to it. 
Also, initializes required variables and allocates memory.*/
TArrList* __new_array_list()
{
    p_arr_test head = (p_arr_test)malloc(sizeof(struct ArrayTest));
    head->next = NULL;
    head->expected = 0;
    head->to_test = 0;
    head->type = -1;

    TArrList *list = (TArrList *)malloc(sizeof(TArrList));
    list->head = head;
    list->qtt = 0;

    return list;
}

/*@brief Adds a test to the beginning of the list.*/
void __add_array_test(TArrList *list, void* expect, void* test, 
                 int expected_size, int test_size, int d_type, int line)
{
    p_arr_test novo = (p_arr_test)malloc(sizeof(TArrTest));
    novo->expected = expect;
    novo->expected_size = expected_size;
    novo->to_test = test;
    novo->to_test_size = test_size;
    novo->type = d_type;
    novo->line = line;

    // insere no início da lista
    novo->next = list->head->next;
    list->head->next = novo;

    list->qtt++;
}

/* @brief Returns a pointer to the first test 
and removes it from the list, returns NULL if 
the list is empty.*/
p_arr_test __pop_array(TArrList *list)
{
    if (list->qtt == 0)
        return NULL;

    p_arr_test aux = list->head->next;
    list->head->next = aux->next;
    list->qtt--;

    return aux;
}


struct arrayTestsList ArrayTestsList = {
    .new_list = __new_array_list,
    .add = __add_array_test,
    .pop = __pop_array,
};
