#include "build/temp/_test_editdist.c"
#include "src/editdist.h"
#include "C:/Users/igors/My_Code/PureC/PureC_tests2/EDIT_DIST/vendor/ceedling/vendor/unity/src/unity.h"


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

    UnityMessage(("Memory allocated"), 25);



    for (i=0; i<4; i++)

        UnityAssertEqualIntArray(( const void*)((test_zero_matrix[i])), ( const void*)((created_matrix[i])), (UNITY_UINT32)((5)), (

       ((void *)0)

       ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);



    for (i=0; i<4; i++)

        free((void *) created_matrix[i]);

    free((void *) created_matrix);



    UnityMessage(("Memory freed"), 34);

}



void test_edit_distance_matrix(void)

{

    struct my_matrix test_word_table1, test_word_table2, test_word_table3, test_word_table4, test_word_table5;



    char *test_table1[5] = {"This", "is", "a", "test", "string"};

    char *test_table2[5] = {"This", "is", "a", "test", "string"};

    char *test_table3[6] = {"This", "is", "a", "different", "test", "string"};

    char *test_table4[0] = {};

    char *test_table5[0] = {};



    test_word_table1.table = test_table1;

    test_word_table1.rows = 5;

    test_word_table1.max_len = 5000;



    test_word_table2.table = test_table2;

    test_word_table2.rows = 5;

    test_word_table2.max_len = 5000;



    test_word_table3.table = test_table3;

    test_word_table3.rows = 6;

    test_word_table3.max_len = 5000;



    test_word_table4.table = test_table4;

    test_word_table4.rows = 0;

    test_word_table4.max_len = 5000;



    test_word_table5.table = test_table5;

    test_word_table5.rows = 0;

    test_word_table5.max_len = 5000;



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((edit_distance_matrix(&test_word_table1, &test_word_table2))), (

   ((void *)0)

   ), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((test_word_table3.rows - test_word_table1.rows)), (UNITY_INT)((edit_distance_matrix(&test_word_table1, &test_word_table3))), (

   ((void *)0)

   ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((test_word_table1.rows)), (UNITY_INT)((edit_distance_matrix(&test_word_table1, &test_word_table4))), (

   ((void *)0)

   ), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((edit_distance_matrix(&test_word_table4, &test_word_table5))), (

   ((void *)0)

   ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT);

}
