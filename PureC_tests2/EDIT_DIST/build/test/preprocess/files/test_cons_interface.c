#include "build/temp/_test_cons_interface.c"
#include "src/user_input_check.h"
#include "src/cons_interface.h"
#include "C:/Users/igors/My_Code/PureC/PureC_tests2/EDIT_DIST/vendor/ceedling/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_console_interface(void)

{

    int path_size = 32767;

    char path_file_real[32767];

    char WIN_kernel_file[] = "\\kernel32.dll";



    

   GetSystemDirectoryA

                     (path_file_real, path_size);



    strcat(path_file_real, WIN_kernel_file);



    char path_fake1[] = "Some_fake_file1";

    char path_fake2[] = "Some_fake_file2";

    char path_fake3[] = "Some_fake_file3";



    char test_path1[300];

    char test_path2[300];

    char test_path_res_file[300];



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_fake1, path_fake2, path_fake3))), (

   ((void *)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_fake1, path_fake2, path_file_real))), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_fake1, path_file_real, path_fake3))), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_fake1, path_file_real, path_file_real))), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_file_real, path_fake2, path_fake3))), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_file_real, path_fake2, path_file_real))), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_file_real, path_file_real, path_fake3))), (

   ((void *)0)

   ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_file_real, path_file_real, path_file_real))), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);

}
