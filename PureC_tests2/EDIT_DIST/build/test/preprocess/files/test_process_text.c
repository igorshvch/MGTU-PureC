#include "build/temp/_test_process_text.c"
#include "src/editdist.h"
#include "src/strtbl.h"
#include "src/readwrite.h"
#include "src/process_text.h"
#include "C:/Users/igors/My_Code/PureC/PureC_tests2/EDIT_DIST/vendor/ceedling/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_count_edit_dist(void)

{

    FILE *input;

    char *test_str1, *test_str2, *test_str3, *test_str4, *test_str5;



    test_str1 = "This is a test string1|";

    test_str2 = "This is a test string1|";



    test_str3 = "This is a test string with differnet words|";

    test_str4 = "";

    test_str5 = "";



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((count_edit_dist(1, "", "", input, test_str1, test_str2))), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((4)), (UNITY_INT)((count_edit_dist(1, "", "", input, test_str1, test_str3))), (

   ((void *)0)

   ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((5)), (UNITY_INT)((count_edit_dist(1, "", "", input, test_str1, test_str4))), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((count_edit_dist(1, "", "", input, test_str4, test_str5))), (

   ((void *)0)

   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT);

}
