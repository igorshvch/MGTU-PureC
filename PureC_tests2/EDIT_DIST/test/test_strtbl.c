#include "unity.h"
#include "strtbl.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_create_string_table(void)
{
    int i;
    char *test_string = "This is a test string";
    EMPT_CHAR_MATRIX test_word_tabel, *res_word_tabel;

    char *test_table[5] = {"This", "is", "a", "test", "string"};

    test_word_tabel.table = test_table;
    test_word_tabel.rows = 5;
    test_word_tabel.max_len = CHAR_MATRIX_ROWS;

    res_word_tabel = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    res_word_tabel->max_len = CHAR_MATRIX_ROWS;
    res_word_tabel->rows = 0;
    res_word_tabel->table = (char**) calloc(res_word_tabel->max_len, sizeof(char*));
    for (i=0; i<5; i++) 
        res_word_tabel->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    
    TEST_MESSAGE("Memory allocated");

    create_string_table(test_string, res_word_tabel);

    TEST_ASSERT_EQUAL(test_word_tabel.max_len, res_word_tabel->max_len);
    TEST_ASSERT_EQUAL(test_word_tabel.rows, res_word_tabel->rows);
    for (i=0; i<5; i++)
        TEST_ASSERT_EQUAL_STRING(test_word_tabel.table[i], res_word_tabel->table[i]);

    for (i=0; i<5; i++) {
        free((void *) res_word_tabel->table[i]);
    }
    free((void *) res_word_tabel->table);
    free((void *) res_word_tabel);
    TEST_MESSAGE("Memory freed");
}