#include "unity.h"
#include "cons_interface.h"
#include "user_input_check.h"

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

    GetSystemDirectory(path_file_real, path_size);

    strcat(path_file_real, WIN_kernel_file);

    char path_fake1[] = "Some_fake_file1";
    char path_fake2[] = "Some_fake_file2";
    char path_fake3[] = "Some_fake_file3";
    
    char test_path1[300];
    char test_path2[300];
    char test_path_res_file[300];

    TEST_ASSERT_EQUAL_INT(1, console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_fake1, path_fake2, path_fake3));
    TEST_ASSERT_EQUAL_INT(1, console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_fake1, path_fake2, path_file_real));
    TEST_ASSERT_EQUAL_INT(1, console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_fake1, path_file_real, path_fake3));
    TEST_ASSERT_EQUAL_INT(1, console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_fake1, path_file_real, path_file_real));
    TEST_ASSERT_EQUAL_INT(1, console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_file_real, path_fake2, path_fake3));
    TEST_ASSERT_EQUAL_INT(1, console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_file_real, path_fake2, path_file_real));
    TEST_ASSERT_EQUAL_INT(1, console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_file_real, path_file_real, path_fake3));
    TEST_ASSERT_EQUAL_INT(0, console_interface(test_path1, test_path2, test_path_res_file, 1, UnityPrint, UnityPrint, path_file_real, path_file_real, path_file_real));
}