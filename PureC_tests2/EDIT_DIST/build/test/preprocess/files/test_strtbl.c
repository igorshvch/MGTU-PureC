#include "build/temp/_test_strtbl.c"
#include "src/strtbl.h"
#include "C:/Users/igors/My_Code/PureC/PureC_tests2/EDIT_DIST/vendor/ceedling/vendor/unity/src/unity.h"


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

    struct my_matrix test_word_tabel, *res_word_tabel;



    char *test_table[5] = {"This", "is", "a", "test", "string"};



    test_word_tabel.table = test_table;

    test_word_tabel.rows = 5;

    test_word_tabel.max_len = 5000;



    res_word_tabel = (struct my_matrix*) malloc(sizeof(struct my_matrix));

    res_word_tabel->max_len = 5000;

    res_word_tabel->rows = 0;

    res_word_tabel->table = (char**) calloc(res_word_tabel->max_len, sizeof(char*));

    for (i=0; i<5; i++)

        res_word_tabel->table[i] = (char*) calloc(400, sizeof(char));



    UnityMessage(("Memory allocated"), 31);



    create_string_table(test_string, res_word_tabel);



    UnityAssertEqualNumber((UNITY_INT)((test_word_tabel.max_len)), (UNITY_INT)((res_word_tabel->max_len)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((test_word_tabel.rows)), (UNITY_INT)((res_word_tabel->rows)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);

    for (i=0; i<5; i++)

        UnityAssertEqualString((const char*)((test_word_tabel.table[i])), (const char*)((res_word_tabel->table[i])), (

       ((void *)0)

       ), (UNITY_UINT)(38));



    for (i=0; i<5; i++) {

        free((void *) res_word_tabel->table[i]);

    }

    free((void *) res_word_tabel->table);

    free((void *) res_word_tabel);

    UnityMessage(("Memory freed"), 45);

}
