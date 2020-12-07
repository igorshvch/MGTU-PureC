#include "build/temp/_test_readwrite.c"
#include "src/readwrite.h"
#include "C:/Users/igors/My_Code/PureC/PureC_tests2/EDIT_DIST/vendor/ceedling/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_read_from_file(void)

{

    FILE *input;

    char *test_str, *read_str;



    test_str = "This is a test string|";



    UnityAssertEqualString((const char*)((test_str)), (const char*)((read_from_file(1, input, test_str, ""))), (

   ((void *)0)

   ), (UNITY_UINT)(19));

}
