#include "stdlib.h"
#include "stdio.h"
#include "tests.h"
#include "Lists/testsList.c"
#include "Lists/arrayTestsList.c"

/* Initializes a tester. */
#define init_tester() STester *tester = _new_tester()

// The var 'type' is widely used through the program, 
// Here is a table for what it represents
/**************
 * var 'type' *
 **************
 * 1 = char   *
 * 2 = int    *
 * 3 = float  *
 * 4 = double *
 **************/

/* @brief Adds a numeric test
   @param A first element to compare
   @param B second element to compare */
#define add_test(A, B) _Generic((A), int: TestsList.add(tester->tests_list, (ll)A, (ll)B, 2, __LINE__), \
                                     float: TestsList.add(tester->tests_list, (ll)A, (ll)B, 3, __LINE__), \
                                     double: TestsList.add(tester->tests_list, (ll)A, (ll)B, 4, __LINE__))

/* @brief Adds a char test
   @param A first element to compare
   @param B second element to compare */
#define add_test_char(A, B) TestsList.add(tester->tests_list, (ll)A, (ll)B, 1, __LINE__)

/* @brief Adds an array test
   @param A first array to compare
   @param B second array to compare
   @param SIZE_A size of first array
   @param SIZE_B size of second array */
#define add_test_arr(A, B, SIZE_A, SIZE_B) _Generic((A), char*: ArrayTestsList.add(tester->tests_list_arr, (void*)A, (void*)B, SIZE_A, SIZE_B, 1, __LINE__), \
                                                         int*: ArrayTestsList.add(tester->tests_list_arr, (void*)A, (void*)B, SIZE_A/4, SIZE_B/4, 2, __LINE__), \
                                                         float*: ArrayTestsList.add(tester->tests_list_arr, (void*)A, (void*)B, SIZE_A/4, SIZE_B/4, 3, __LINE__), \
                                                         double*: ArrayTestsList.add(tester->tests_list_arr, (void*)A, (void*)B, SIZE_A/8, SIZE_B/8, 4, __LINE__)) 

/* Runs all added tests. */
#define run_tests() \
_run_tests(tester); \
_run_arr_tests(tester);

#define PRINT_ELEMENT(element) \
do { \
    _Generic((element), \
        char: printf("%c", (char)(element)), \
        int: printf("%d", (int)(element)), \
        unsigned int: printf("%u", (unsigned int)(element)), \
        float: printf("%.3f", (float)(element)), \
        double: printf("%.3lf", (double)(element)), \
        default: printf("Unsupported type") \
    ); \
} while (0)

#define PRINT_ARRAY(arr, len) \
do { \
    printf("["); \
    for (int i = 0; i < len; i++) { \
        PRINT_ELEMENT(arr[i]); \
        if (i != len-1) { \
            printf(", "); \
        } \
    } \
    printf("]"); \
} while (0)

/* Prints a failed test in the folowing format:
Line 'line': Expected-> 'A' / Tested-> 'B'*/
#define print_fail(line, A, B, type) \
    printf("\nLine %i:", line); \
    printf("\nExpected-> "); \
    print_generic_element(A, type); \
    printf("\nTested->   "); \
    print_generic_element(B, type); \
    printf("\n");

/* Prints a failed array test in the folowing format:
Line 'line': Expected-> 'arr_A' / Tested-> 'arr_B'*/
#define print_fail_array(arr_A, arr_B, size_a, size_b, line, type) \
    printf("\nLine %i:", line); \
    printf("\nExpected-> "); \
    print_generic_array(arr_A, size_a, type); \
    printf("\nTested->   "); \
    print_generic_array(arr_B, size_b, type); \
    printf("\n"); \

struct Tester
{
    TList *tests_list; //List that holds simple tests
    TArrList *tests_list_arr; //List that holds array tests
};

STester* _new_tester()
{
    STester *tester = (STester *)malloc(sizeof(struct Tester));
    tester->tests_list = TestsList.new_list();
    tester->tests_list_arr = ArrayTestsList.new_list();

    return tester;
}

/* @brief Returns 1 if array A is equal to array B, 0 otherwise.*/
int _is_equal_arr(void *A, void *B, int A_len, int B_len, int type)
{
    if (A_len != B_len)
    {
        return 0; // failed
    }
    else
    {
        switch (type)
        {
        case 1:
            for (int i = 0; i < A_len; i++)
            {
                if (((char*)A)[i] != ((char*)B)[i])
                {
                    return 0; //failed
                }
            }      
        break;

        case 2:
            for (int i = 0; i < A_len; i++)
            {
                if (((int*)A)[i] != ((int*)B)[i])
                {
                    return 0; //failed
                }
            }      
        break;

        case 3:
            for (int i = 0; i < A_len; i++)
            {
                if (((float*)A)[i] != ((float*)B)[i])
                {
                    return 0; //failed
                }
            }      
        break;

        case 4:
            for (int i = 0; i < A_len; i++)
            {
                if (((double*)A)[i] != ((double*)B)[i])
                {
                    return 0; //failed
                }
            }      
        break;
                
        default:
            break;
        }
        
    }
    return 1; // success
}

/* Using the macro PRINT_ELEMENT, and the var type, 
this function prints a element stored in a 'long long int' 
as the intend type.*/
void print_generic_element(ll elem, int type)
{
    switch (type)
    {
    case 1:
        PRINT_ELEMENT((char)(elem));
        break;

    case 2:
        PRINT_ELEMENT((int)(elem));
        break;

    case 3:
        PRINT_ELEMENT((float)(elem));
        break;

    case 4:
        PRINT_ELEMENT((double)(elem));
        break;
    
    default:
        break;
    }    
}

/* This function tests all simple tests and prints the results.*/
void _run_tests(STester *tester)
{
    TList *list = tester->tests_list; //The list with all tests
    const int n_tests = list->qtt;    //The number of tests in the list
    int results[n_tests];             //The tests results (0 = success, 1 = fail)
    int all_passed = 1;               //if 1 all tests were successfull, 0 if any test failed
    int n_fails = 0;                  //The number of tests that failed
    p_test tests_failed[n_tests];     //An array with the failed tests pointers

    int i = 0;
    p_test pos = TestsList.pop(list); //Gets the first test
    while (pos != NULL)
    {
        if (pos->tested == pos->expected) //Makes the comparison
            results[i] = 0; //Test success
        else //Test failed
        {
            results[i] = 1; 
            tests_failed[n_fails] = pos;
            n_fails++;
            all_passed = 0;
        }
        i++;
        pos = TestsList.pop(list); //Gets the next test
    }

    printf("**********************SIMPLE TESTS**********************\n\n");

    if (all_passed)
        printf("All tests successful!\n\n");
    else
    {
        //Prints the results (0=success, 1=fail)
        printf("Results:\n");
        for (int j = n_tests-1; j >= 0; j--) 
        {
            printf("%i", results[j]); 
        }

        printf("\n\nPassed: %i", n_tests-n_fails); //Prints how many tests passed
        printf("\nFailed: %i", n_fails); //Prints how many tests failed

        printf("\n\n******** Tests that failed ********\n");
        //Cycles by all failed tests in 'tests_failed'
        for (int j = n_fails-1; j >= 0; j--)
        {
            int line = tests_failed[j]->line;
            ll expect = tests_failed[j]->expected;
            ll tested = tests_failed[j]->tested;
            int type = tests_failed[j]->type;

            print_fail(line, expect, tested, type); //Prints all info about the failed test
        }
        printf("\n\n");
    }
}

/* Using the macro PRINT_ARRAY, and the var type, 
this function prints a generic array.*/
void print_generic_array(void* arr, int len, int type)
{
    switch (type)
    {
    case 1:
        printf("%s", ((char*)arr));
        break;

    case 2:
        PRINT_ARRAY(((int*)arr), len);
        break;

    case 3:
        PRINT_ARRAY(((float*)arr), len);
        break;

    case 4:
        PRINT_ARRAY(((double*)arr), len);
        break;
    
    default:
        break;
    }    
}

/* This function tests all array tests and prints the results.*/
void _run_arr_tests(STester *tester)
{
    TArrList *list = tester->tests_list_arr; //The list with all tests
    const int n_tests = list->qtt;           //The number of tests in the list
    int results[n_tests];                    //The tests results (0 = success, 1 = fail)
    int all_passed = 1;                      //if 1 all tests were successful, 0 if any test failed
    int n_fails = 0;                         //The number of tests that failed
    p_arr_test tests_failed[n_tests];        //An array with the failed tests pointers

    int i = 0;
    p_arr_test pos = ArrayTestsList.pop(list); //Gets the first test
    while (pos != NULL)
    {
        //Makes the comparison and stores it in x
        int x = _is_equal_arr(pos->expected, 
                              pos->to_test, 
                              pos->expected_size, 
                              pos->to_test_size, 
                              pos->type); 
        if (x) 
            results[i] = 0; //Test success
        else //Test failed
        {
            results[i] = 1;
            tests_failed[n_fails] = pos;
            n_fails++;
            all_passed = 0;
        }
        i++;
        pos = ArrayTestsList.pop(list); //Gets the next test
    }

    printf("\n**********************ARRAY TESTS**********************\n\n");


    if (all_passed)
        printf("All tests successful!\n\n");
    else
    {
        //Prints the results (0=success, 1=fail)
        printf("Results:\n");
        for (int j = n_tests-1; j >= 0; j--) 
        {
            printf("%i", results[j]);
        }

        printf("\n\nPassed: %i", n_tests-n_fails); //Print how many tests passed
        printf("\nFailed: %i", n_fails); //Print how many tests failed

        printf("\n\n******** Tests that failed ********\n");
        //Cycles by all failed tests in 'tests_failed'
        for (int j = n_fails-1; j >= 0; j--)
        {
            void* expect = tests_failed[j]->expected;
            void* tested = tests_failed[j]->to_test;
            int expect_size = tests_failed[j]->expected_size;
            int tested_size = tests_failed[j]->to_test_size;
            int line = tests_failed[j]->line;
            int type = tests_failed[j]->type;

            //Prints all info about the failed test
            print_fail_array(expect, tested, expect_size, tested_size, line, type);
        }
        


        printf("\n\n");
    }
}
