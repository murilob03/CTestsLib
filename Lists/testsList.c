#include <stdio.h>
#include <stdlib.h>
#include "testsList.h"

typedef struct Test *p_test;

struct Test
{
    ll expected;
    ll tested;
    int type;
    int line;
    TTest *next;
};

struct List
{
    p_test head;
    int qtt;
};

/*@brief Creates a list and returns a pointer to it. 
Also, initializes required variables and allocates memory.*/
TList* __new_list()
{
    p_test head = (p_test)malloc(sizeof(struct Test));
    head->next = NULL;
    head->expected = 0;
    head->tested = 0;
    head->type = -1;

    TList *list = (TList *)malloc(sizeof(TList));
    list->head = head;
    list->qtt = 0;

    return list;
}

/*@brief Adds a test to the beginning of the list.*/
void __add_test(TList *list, ll a, ll b, int type, int line)
{
    p_test novo = (p_test)malloc(sizeof(TTest));
    novo->expected = a;
    novo->tested = b;
    novo->type = type;
    novo->line = line;

    // insere no início da lista
    novo->next = list->head->next;
    list->head->next = novo;

    list->qtt++;
}

/* @brief Returns a pointer to the first test 
and removes it from the list, returns NULL if 
the list is empty.*/
p_test __pop(TList *list)
{
    if (list->qtt == 0)
        return NULL;

    p_test aux = list->head->next;
    list->head->next = aux->next;
    list->qtt--;

    return aux;
}

struct testsList TestsList = {
    .new_list = __new_list,
    .add = __add_test,
    .pop = __pop,
};
