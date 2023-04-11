#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

/*
This interface defines a List to store tests.

*******This interface was designed for specifc use*******
*/

/* Exported type */
typedef struct List TList;
typedef struct Test TTest;

typedef long double ll;

/* Define a struct to encapsulate functions */
struct testsList
{
    /*@brief Creates a new list and returns a pointer to it.*/
    TList* (*new_list)();
    /*@brief Adds a test in the beginning of the list */
    void (*add)(TList* list, ll a, ll b, int type, int line);
    /*@brief Returns a pointer to the first test 
    and removes it from the list, returns NULL if 
    the list is empty.*/
    TTest* (*pop)(TList* list);
};

/* Declares a global struct */
extern struct testsList TestsList;


TList* __new_list();

void __add_test(TList *list, ll expect, ll test, int d_type, int line);

TTest* __pop(TList *list);

#endif
