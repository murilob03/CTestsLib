# CTestsLib
## Introduction
CTestsLib is a free and simple library designed to automate testing using the C language. It supports various data types and provides two types of tests: simple tests and array tests.

## General Information
This library has been tested and verified to work with the following compilers:

- Clang (version 15.0.7)
- GCC (version 12.2.1)

## Setup
To use CTestsLib in your project, follow these steps:

1. Download the CTestsLib folder and place it inside your project folder.
2. Create a file to deploy your tests (e.g. tests.c).
3. Include the tests.c file in your project.

## Suported tests types
CTestsLib supports the following data types:
- char
- int
- float
- double

## How to Test
To perform tests using CTestsLib, follow these steps:

1. Initialize your tester using init_tester().
2. Add your tests (simple tests, array tests or both).
3. Run the tests you've added using run_tests().

### Adding simple Tests
Simple tests involve comparing two elements (e.g. int x int, double x double).
To use this type of test, follow these steps:

1. Initialize your tester using init_tester().
2. Add your tests using add_test(A, B):
    - This compares A and B and works for any supported type except for chars.
    - To compare chars, use add_test_char(A, B).
3. Run the tests you've added using run_tests().

#### Example

    #include "CTestsLib/tests.c"

    int main() 
    {
        init_tester();

        add_test(1, 2);
        add_test(2, 2);
        add_test(2.0, 2.7);
        add_test(2.0, 3.0);
        add_test_char('a', 'b'); // Use add_test_char to test chars

        run_tests();
    }

### Adding array Tests
Array tests involve comparing two arrays (e.g. int[] x int[], str x str).
To use this type of test, follow these steps:

1. Initialize your tester using init_tester().
2. Add your tests using add_test_arr(A, B, A_size, B_size):
    - This compares A and B element by element.
    - A_size and B_size should be the size of the arrays in bytes.
    - This works for any supported type including chars (strings).
3. Run the tests you've added using run_tests().

#### Example

    #include "CTestsLib/tests.c"

    int main() 
    {
        init_tester();

        int a[] = {1, 2, 2};
        int b[] = {1, 2, 1};
        add_test_arr(a, b, sizeof(a), sizeof(b));

        char c[] = "Hello world!";
        char d[] = "Hello world!";
        add_test_arr(c, d, sizeof(c), sizeof(d));

        run_tests();
    }

## Reading the Output
The output will look like this:

    **********************SINGLE TESTS**********************
    Results:
    10101
    Passed: 2
    Failed: 3

    ******** Tests that failed ********
    Line 7:
    Expected -> 1
    Tested -> 2

    Line 9:
    Expected -> 2.000
    Tested -> 2.700

    Line 11:
    Expected -> a
    Tested -> b

    **********************ARRAY TESTS**********************
    All tests successful!

If all tests were successful, the output will simply say "All tests successful!" If any test failed, the output will include:

- The test results (0 for successful tests and 1 for failed tests)
- The number of tests that passed and that failed
- Test-by-test details for the failed tests:
    - The line on which the test was added
    - The expected value (A)
    - The value that was tested (B)