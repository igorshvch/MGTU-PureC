#include "cons_interface.h"

/*
int console_interface(char* path_folder, char* path_res_file, int (*proc_func)(char*))
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
            printf("Введите полный путь к папке с файлами:\n");
            scanf("%s", inputstring);
            status = (*proc_func)(inputstring);
            if (status) {
                printf("Ошибка при вводе пути к папке\n");
                continue;
            }
            flag1 = 1;
            path_folder = inputstring;
        }
        if (!flag2) {
            printf("Введите полный путь к файлу для записи результатов:\n");
            scanf("%s", inputstring);
            status = (*proc_func)(inputstring);
            if (status) {
                printf("Ошибка при вводе пути к файлу записи результатов\n");
                continue;
            }
            flag2 = 1;
            path_res_file = inputstring;
        }
        if (flag1 && flag2) {
            printf("Вы ввели:\n");
            printf("Каталог с файлами: %s\n", path_folder);
            printf("Файл для записи результата: %s\n", path_res_file);
            switcher = 0;
        }
    }
}
*/