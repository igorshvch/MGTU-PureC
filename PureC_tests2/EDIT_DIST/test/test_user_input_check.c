#include "unity.h"
#include "user_input_check.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_verify_not_too_long_file(void)
{
    int i = 0;
    char test_str1[] = "string_of_proper_length";
    char test_str2[MAX_PATH+1]; 

    for (i=0; i<MAX_PATH; i++)
        test_str2[i] = 's';
    test_str2[i] = '\0';
    TEST_ASSERT_EQUAL_INT(0, verify_not_too_long_file(test_str1));
    TEST_ASSERT_EQUAL_INT(1, verify_not_too_long_file(test_str2));
}

void test_verify_not_too_long_dir(void)
{
    int i = 0;
    char test_str1[] = "string_of_proper_length";
    char test_str2[(MAX_PATH/2)+1];

    for (i=0; i<(MAX_PATH/2); i++)
        test_str2[i] = 's';
    test_str2[i] = '\0';
    TEST_ASSERT_EQUAL_INT(0, verify_not_too_long_dir(test_str1));
    TEST_ASSERT_EQUAL_INT(1, verify_not_too_long_dir(test_str2));
}

void test_verify_only_valid_symbols(void)
{
    srand(2);

    int i, j;
    int invalid_symbols_position[7];
    const int range = 258;
    
    char message_cash[1000];
    char invalid_symbols[7] = {':', '*', '?', '\"', '<', '>', '|'};
    char invalid_strings[7][MAX_PATH];
    char valid_string[] = "some_strging_without_invalid_symbols";

    for (i=0; i<7; i++) {
        for (j=0; j<MAX_PATH-1; j++)
            invalid_strings[i][j] = 's';
        invalid_strings[i][j] = '\0';
        invalid_symbols_position[i] = rand() % range;
        invalid_strings[i][invalid_symbols_position[i]] = invalid_symbols[i];
    }

    for (i=0; i<7; i++) {
        sprintf(message_cash, "Invalid symbol \'%c\' at position %d", invalid_symbols[i], invalid_symbols_position[i]);
        TEST_MESSAGE(message_cash);
        TEST_ASSERT_EQUAL_INT(1, verify_only_valid_symbols(invalid_strings[i]));
    }
    TEST_ASSERT_EQUAL_INT(0, verify_only_valid_symbols(valid_string)); 
}

void test_verify_file_path_as_valid(void)
{
    int path_size = 32767; //https://docs.microsoft.com/en-us/windows/win32/sysinfo/getting-system-information
    char path_real[32767];
    char path_fake[32767];

    char message_cash[1000];
    
    char WIN_kernel_file[] = "\\kernel32.dll";
    char fake_file[] = "\\file_name.exe";

    GetSystemDirectory(path_real, path_size);
    GetSystemDirectory(path_fake, path_size);

    strcat(path_real, WIN_kernel_file);
    strcat(path_fake, fake_file);

    sprintf(&(message_cash[0]), "REAL file path: %s", path_real);
    TEST_MESSAGE(message_cash);
    sprintf(&(message_cash[0]), "FAKE file path: %s", path_fake);
    TEST_MESSAGE(message_cash);

    TEST_ASSERT_EQUAL_INT(0, verify_file_path_as_valid(path_real));
    TEST_ASSERT_EQUAL_INT(1, verify_file_path_as_valid(path_fake));
}

void test_verify_dir_path_as_valid(void)
{
    int path_size = 32767;
    char path_real[32767];

    char path_fake[] = "C:\\Directory\\path";

    char message_cash[1000];

    GetSystemDirectory(path_real, path_size);

    sprintf(&(message_cash[0]), "REAL directory path: %s", path_real);
    TEST_MESSAGE(message_cash);
    sprintf(&(message_cash[0]), "FAKE file path: %s", path_fake);
    TEST_MESSAGE(message_cash);

    TEST_ASSERT_EQUAL_INT(0, verify_dir_path_as_valid(path_real));
    TEST_ASSERT_EQUAL_INT(1, verify_dir_path_as_valid(path_fake));
}

void test_change_backslash_to_slash(void)
{
    char test_str_slash[] = "\\\\\\\\\\\\\\\\\\\\";
    char test_str_char[] = "ssssssssss";
    
    char message_cash[1000];

    sprintf(&(message_cash[0]), "Test string before alteration: %10s", test_str_slash);
    TEST_MESSAGE(message_cash);

    TEST_ASSERT_EQUAL_INT(0, change_backslash_to_slash(test_str_slash));
    TEST_ASSERT_EACH_EQUAL_CHAR('/', test_str_slash, strlen(test_str_slash));

    sprintf(&(message_cash[0]), "Test string after alteration: %11s", test_str_slash);
    TEST_MESSAGE(message_cash);

    sprintf(&(message_cash[0]), "Test string before alteration: %10s", test_str_char);
    TEST_MESSAGE(message_cash);

    TEST_ASSERT_EQUAL_INT(1, change_backslash_to_slash(test_str_char));
    TEST_ASSERT_EACH_EQUAL_CHAR('s', test_str_char, strlen(test_str_char));

    sprintf(&(message_cash[0]), "Test string after alteration: %11s", test_str_char);
    TEST_MESSAGE(message_cash);
}