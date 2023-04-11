#include "tests.c"

int main()
{
    init_tester();

    add_test(1, 2);
    add_test(2, 2);
    add_test(2.0, 2.7);
    add_test(2.0, 3.0);
    add_test_char('a', 'b');

    int a[] = {1, 2, 2};
    int b[] = {1, 2, 1};
    add_test_arr(a, b, 3, 3);

    char c[] = "aac";
    char d[] = "aaa";
    add_test_arr(c, d, 3, 3);

    float e[] = {1.0f, 2.0f, 3.1f};
    float f[] = {1.0f, 2.0f, 3.0f};
    add_test_arr(e, f, 3, 3);

    double g[] = {1.0, 2.0, 3.2};
    double h[] = {1.0, 2.0, 3.0};
    add_test_arr(g, h, 3, 3);

    double i[] = {1.0, 2.7, 3.3, -4.0};
    double j[] = {1.0, 2.7, 3.3, -4.0};
    add_test_arr(i, j, 4, 4);

    char k[] = "Hello Worl!";
    char l[] = "Hello World!";
    add_test_arr(k, l, sizeof(k), sizeof(l));

    int x[] = {1, 2, 1, -1};
    int y[] = {1, 2, 1, -2};
    add_test_arr(x, y, sizeof(x), sizeof(y));


    run_tests();
}