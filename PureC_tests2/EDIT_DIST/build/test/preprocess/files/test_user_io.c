#include "build/temp/_test_user_io.c"
#include "src/user_io.h"
#include "C:/Users/igors/My_Code/PureC/PureC_tests2/EDIT_DIST/vendor/ceedling/vendor/unity/src/unity.h"








void setUp(void)

{

}



void tearDown(void)

{

}



void test_verify_not_too_long_WIN1(void)

{

    int i = 0;

    char test_str[260];



    for (i=0; i<260 +1; i++)

        test_str[i] = 'c';



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((verify_not_too_long_WIN("Some_test"))), (

   ((void *)0)

   ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((verify_not_too_long_WIN(test_str))), (

   ((void *)0)

   ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((verify_not_too_long_WIN("Some_test"))), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((verify_not_too_long_WIN(test_str))), (

   ((void *)0)

   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT);

}
