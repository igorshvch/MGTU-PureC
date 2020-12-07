#include "unity.h"
#include "editdist.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_create_zero_matrix(void)
{
    int i;
    int test_zero_matrix[4][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
    };

    int **created_matrix;

    created_matrix = create_zero_matrix(4, 5);
    TEST_MESSAGE("Memory allocated");

    for (i=0; i<4; i++)
        TEST_ASSERT_EQUAL_INT_ARRAY(test_zero_matrix[i], created_matrix[i], 5);

    for (i=0; i<4; i++)
        free((void *) created_matrix[i]);
    free((void *) created_matrix);

    TEST_MESSAGE("Memory freed");
}

void test_edit_distance_matrix(void)
{
    EMPT_CHAR_MATRIX test_word_table1, test_word_table2, test_word_table3, test_word_table4, test_word_table5;

    char *test_table1[5] = {"This", "is", "a", "test", "string"};
    char *test_table2[5] = {"This", "is", "a", "test", "string"};
    char *test_table3[6] = {"This", "is", "a", "different", "test", "string"};
    char *test_table4[0] = {};
    char *test_table5[0] = {};

    test_word_table1.table = test_table1;
    test_word_table1.rows = 5;
    test_word_table1.max_len = CHAR_MATRIX_ROWS;

    test_word_table2.table = test_table2;
    test_word_table2.rows = 5;
    test_word_table2.max_len = CHAR_MATRIX_ROWS;

    test_word_table3.table = test_table3;
    test_word_table3.rows = 6;
    test_word_table3.max_len = CHAR_MATRIX_ROWS;

    test_word_table4.table = test_table4;
    test_word_table4.rows = 0;
    test_word_table4.max_len = CHAR_MATRIX_ROWS;

    test_word_table5.table = test_table5;
    test_word_table5.rows = 0;
    test_word_table5.max_len = CHAR_MATRIX_ROWS;

    TEST_ASSERT_EQUAL_INT(0, edit_distance_matrix(&test_word_table1, &test_word_table2));
    TEST_ASSERT_EQUAL_INT(test_word_table3.rows - test_word_table1.rows, edit_distance_matrix(&test_word_table1, &test_word_table3));
    TEST_ASSERT_EQUAL_INT(test_word_table1.rows, edit_distance_matrix(&test_word_table1, &test_word_table4));
    TEST_ASSERT_EQUAL_INT(0, edit_distance_matrix(&test_word_table4, &test_word_table5));
}