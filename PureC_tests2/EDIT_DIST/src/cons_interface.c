#include "cons_interface.h"

int console_interface(
    char* path_file1,
    char* path_file2,
    char* path_res_file,
    int test_mode,
    void (*print_f)(const char*),
    void (*scan_f)(const char*),
    char* test_str1,
    char* test_str2,
    char* test_str3
)
{
    
    int ER_flag1, ER_flag2, ER_flag3, i, j;

    char inputstring[500];
    
    int status_file[4] = {1,1,1,1};

    char *er_file_mess[4] = {
        "ERROR: file name too long\n",
        "ERROR: invalid symbols\n",
        "ERROR: file path is not valid\n",
        "ERROR: couldn\'t change backslashes\n",
    };

    ER_flag1 = 0;
    ER_flag2 = 0;
    ER_flag3 = 0;
////////////////////////////////////////////
    if (test_mode) {
        (*print_f)("Test print 1");
        (*scan_f)("Test scan 2");
        strcpy(inputstring, test_str1);
    }
    else {
        printf("Input path to file1:\n");
        scanf("%s", inputstring);
    }
    status_file[0] = verify_not_too_long_file(inputstring);
    status_file[1] = verify_only_valid_symbols(inputstring);
    status_file[2] = verify_file_path_as_valid(inputstring);
    status_file[3] = change_backslash_to_slash(inputstring);

    for (i = 0; i < 4; i++) {
        if (status_file[i] != 0){
            if (test_mode)
                (*print_f)(er_file_mess[i]);
            else
                printf("%s", er_file_mess[i]);
            ER_flag1 = 1;
            break;
        }
    }

    if (!ER_flag1)
        strcpy(path_file1, inputstring);
////////////////////////////////////////////
    if (test_mode) {
        (*print_f)("Test print 3");
        (*scan_f)("Test scan 4");
        strcpy(inputstring, test_str2);
    }
    else {
        printf("Input path to file2:\n");
        scanf("%s", inputstring);
    }
    status_file[0] = verify_not_too_long_file(inputstring);
    status_file[1] = verify_only_valid_symbols(inputstring);
    status_file[2] = verify_file_path_as_valid(inputstring);
    status_file[3] = change_backslash_to_slash(inputstring);

    for (i = 0; i < 4; i++) {
        if (status_file[i] != 0){
            if (test_mode)
                (*print_f)(er_file_mess[i]);
            else
                printf("%s", er_file_mess[i]);
            ER_flag2 = 1;
            break;
        }
    }

    if (!ER_flag2)
        strcpy(path_file2, inputstring);
////////////////////////////////////////////
    if (test_mode) {
        (*print_f)("Test print 5");
        (*scan_f)("Test scan 6");
        strcpy(inputstring, test_str3);
    }
    else {
        printf("Input path res_file:\n");
        scanf("%s", inputstring);
    }
    status_file[0] = verify_not_too_long_file(inputstring);
    status_file[1] = verify_only_valid_symbols(inputstring);
    status_file[2] = verify_file_path_as_valid(inputstring);
    status_file[3] = change_backslash_to_slash(inputstring);

    for (i = 0; i < 4; i++) {
        if (status_file[i] != 0){
            if (test_mode)
                (*print_f)(er_file_mess[i]);
            else
                printf("%s", er_file_mess[i]);
            ER_flag3 = 1;
            break;
        }
    }

    if (!ER_flag3)
        strcpy(path_res_file, inputstring);
////////////////////////////////////////////
    if (test_mode) {
        (*print_f)("Test print 7");
        (*print_f)(path_file1);
        (*print_f)(path_file2);
        (*print_f)(path_res_file);
        if (!ER_flag1 && !ER_flag2 && !ER_flag3)
            return 0;
        else
            return 1;
    }
    else {
        if (!ER_flag1 && !ER_flag2 && !ER_flag3) {
            printf("Your input is:\n");
            printf("FILE1 PATH: %s\n", path_file1);
            printf("FILE2 PATH: %s\n", path_file2);
            printf("RES_FILE PATH: %s\n", path_res_file);
            return 0;
        }
        else {
            printf("Incorrect input! Programm ternibation");
            return 1;
        }
    }
}

void dumy_print_f(const char* str) {
    ;
}

void dumy_scan_f(const char* str) {
    ;
}