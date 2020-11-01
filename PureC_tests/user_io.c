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
            printf("Введите полный путь к папке с файлами:\n");
            scanf("%s", inputstring);
            status = proc_func(inputstring);
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
            status = process_input_string(inputstring);
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


int verify_not_too_long_WIN(char* str)
{
    if (strlen(str) > (MAX_PATH-1))
        return 1;
    else
        return 0;
}

int verify_only_permitted_symbols_WIN(char* str)
{
    int i;
    char c;

    for (i=0; i<(MAX_PATH-1); i++) {
        c = str[i];
        if (c==':' || c=='*' || c=='?' || c=='\"' || c=='<' || c=='>' || c=='|')
            return 1;
    }
    return 0;
}

int verify_path_is_valid(char* str, char* mode)
{
    DWORD dwAttrib = GetFileAttributes(str);
    
    if (mode=="f") {
        if (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
            return 0;
        else
            return 1;
    } else if (mode=="d") {
        if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
            return 0;
        else
            return 1;
    }
}

void change_backslash_to_slash(char* str)
{
    int i;
    char c;

    for (i=0; i<(MAX_PATH-1); i++) {
        c = str[i];
        if (c=='\\')
            str[i] = '/';
    }
}
