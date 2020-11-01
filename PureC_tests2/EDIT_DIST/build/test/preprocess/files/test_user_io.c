#include "build/temp/_test_user_io.c"
#include "src/user_io.h"
#include "C:/Users/igors/My_Code/PureC/PureC_tests2/EDIT_DIST/vendor/ceedling/vendor/unity/src/unity.h"


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

    char test_str2[

                  260

                          +1];



    for (i=0; i<

               260

                       ; i++)

        test_str2[i] = 's';

    test_str2[i] = '\0';

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((verify_not_too_long_file(test_str1))), (

   ((void *)0)

   ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((verify_not_too_long_file(test_str2))), (

   ((void *)0)

   ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);

}



void test_verify_not_too_long_dir(void)

{

    int i = 0;

    char test_str1[] = "string_of_proper_length";

    char test_str2[(

                   260

                           /2)+1];



    for (i=0; i<(

                260

                        /2); i++)

        test_str2[i] = 's';

    test_str2[i] = '\0';

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((verify_not_too_long_dir(test_str1))), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((verify_not_too_long_dir(test_str2))), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

}



void test_verify_only_valid_symbols(void)

{

    srand(2);



    int i, j;

    int invalid_symbols_position[7];

    const int range = 258;



    char message_cash[1000];

    char invalid_symbols[7] = {':', '*', '?', '\"', '<', '>', '|'};

    char invalid_strings[7][

                           260

                                   ];

    char valid_string[] = "some_strging_without_invalid_symbols";



    for (i=0; i<7; i++) {

        for (j=0; j<

                   260

                           -1; j++)

            invalid_strings[i][j] = 's';

        invalid_strings[i][j] = '\0';

        invalid_symbols_position[i] = rand() % range;

        invalid_strings[i][invalid_symbols_position[i]] = invalid_symbols[i];

    }



    for (i=0; i<7; i++) {

        sprintf(message_cash, "Invalid symbol \'%c\' at position %d", invalid_symbols[i], invalid_symbols_position[i]);

        UnityMessage((message_cash), 61);

        UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((verify_only_valid_symbols(invalid_strings[i]))), (

       ((void *)0)

       ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

    }

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((verify_only_valid_symbols(valid_string))), (

   ((void *)0)

   ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_INT);

}



void test_verify_file_path_as_valid(void)

{

    int path_size = 32767;

    char path_real[32767];

    char path_fake[32767];



    char message_cash[1000];



    char WIN_kernel_file[] = "\\kernel32.dll";

    char fake_file[] = "\\file_name_should_be_here_instead_of_this_dummy_string.exe";



    

   GetSystemDirectoryA

                     (path_real, path_size);

    

   GetSystemDirectoryA

                     (path_fake, path_size);



    strcat(path_real, WIN_kernel_file);

    strcat(path_fake, fake_file);



    sprintf(&(message_cash[0]), "REAL file path: %s", path_real);

    UnityMessage((message_cash), 85);

    sprintf(&(message_cash[0]), "FAKE file path: %s", path_fake);

    UnityMessage((message_cash), 87);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((verify_file_path_as_valid(path_real))), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((verify_file_path_as_valid(path_fake))), (

   ((void *)0)

   ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT);

}



void test_verify_dir_path_as_valid(void)

{

    int path_size = 32767;

    char path_real[32767];



    char path_fake[] = "C:\\Directory\\path";



    char message_cash[1000];



    

   GetSystemDirectoryA

                     (path_real, path_size);



    sprintf(&(message_cash[0]), "REAL directory path: %s", path_real);

    UnityMessage((message_cash), 105);

    sprintf(&(message_cash[0]), "FAKE file path: %s", path_fake);

    UnityMessage((message_cash), 107);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((verify_dir_path_as_valid(path_real))), (

   ((void *)0)

   ), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((verify_dir_path_as_valid(path_fake))), (

   ((void *)0)

   ), (UNITY_UINT)(110), UNITY_DISPLAY_STYLE_INT);

}



void test_change_backslash_to_slash(void)

{

    char test_str_slash[] = "\\\\\\\\\\\\\\\\\\\\";

    char test_str_char[] = "ssssssssss";



    char message_cash[1000];



    sprintf(&(message_cash[0]), "Test string before alteration: %10s", test_str_slash);

    UnityMessage((message_cash), 121);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((change_backslash_to_slash(test_str_slash))), (

   ((void *)0)

   ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualIntArray(UnityNumToPtr((UNITY_INT)(UNITY_INT8 )(('/')), 1), ( const void*)((test_str_slash)), (UNITY_UINT32)((strlen(test_str_slash))), (

   ((void *)0)

   ), (UNITY_UINT)(124), UNITY_DISPLAY_STYLE_CHAR, UNITY_ARRAY_TO_VAL);



    sprintf(&(message_cash[0]), "Test string after alteration: %11s", test_str_slash);

    UnityMessage((message_cash), 127);



    sprintf(&(message_cash[0]), "Test string before alteration: %10s", test_str_char);

    UnityMessage((message_cash), 130);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((change_backslash_to_slash(test_str_char))), (

   ((void *)0)

   ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualIntArray(UnityNumToPtr((UNITY_INT)(UNITY_INT8 )(('s')), 1), ( const void*)((test_str_char)), (UNITY_UINT32)((strlen(test_str_char))), (

   ((void *)0)

   ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_CHAR, UNITY_ARRAY_TO_VAL);



    sprintf(&(message_cash[0]), "Test string after alteration: %11s", test_str_char);

    UnityMessage((message_cash), 136);

}
