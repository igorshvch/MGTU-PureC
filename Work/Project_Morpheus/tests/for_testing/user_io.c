#include "user_io.h"

int console_interface(char* path_folder, char* path_res_file, int proc_func(char*))
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    int switcher, status, flag1, flag2;
    char *inputstring;

    switcher = 1;
    status = 0;
    flag1 = 0;
    flag2 = 0;

    while (switcher) {
        if (!flag1) {
            printf("¬ведите полный путь к папке с файлами:\n");
            scanf("%s", inputstring);
            status = proc_func(inputstring);
            if (status) {
                printf("ќшибка при вводе пути к папке\n");
                continue;
            }
            flag1 = 1;
            path_folder = inputstring;
        }
        if (!flag2) {
            printf("¬ведите полный путь к файлу дл€ записи результатов:\n");
            scanf("%s", inputstring);
            status = process_input_string(inputstring);
            if (status) {
                printf("ќшибка при вводе пути к файлу записи результатов\n");
                continue;
            }
            flag2 = 1;
            path_res_file = inputstring;
        }
    }
}

int process_input_string(char *str)
{
    int i;
    char c;

    if (strlen(str) > (MAX_PATH-1))
        return 1;
    else {
        for (i=0; i<strlen(str); i++) {
            c = str[i];
            if (c==':' || c=='*' || c=='?' || c=='\"' || c=='<' || c=='>' || c=='|')
                return 1;
            if (c=='\\')
                str[i] = '/';
        }
    }
    return 0;
}
