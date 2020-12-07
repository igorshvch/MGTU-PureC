#include "build/temp/_test_sys_test.c"
#include "src/user_input_check.h"
#include "src/editdist.h"
#include "src/strtbl.h"
#include "src/readwrite.h"
#include "src/process_text.h"
#include "src/cons_interface.h"
#include "src/sys_test.h"
#include "C:/Users/igors/My_Code/PureC/PureC_tests2/EDIT_DIST/vendor/ceedling/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_global_test(void)

{

    char *str;



    str = global_test();



    UnityMessage(("First print"), 25);

    UnityMessage((str), 26);



    UnityAssertEqualString((const char*)(("editorial distance equals to 1\n")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(28));

}
