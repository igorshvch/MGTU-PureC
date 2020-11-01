#include "listdir.h"


static int main_test()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    printf("=====================================================\n");
    printf("Тест модуля 'listdir.c'\n");
    printf("=====================================================\n");

    //Объявление переменных
    int rows, j, k, status;
    char **files;

    //Инициализация переменных
    rows = 0; 
    files = (char**) calloc(TEST_TABLE_LEN, sizeof(char*));
    for (j=0; j<TEST_TABLE_LEN; j++)
        files[j] = (char*) calloc(TEST_TABLE_LEN, sizeof(char));

    status = list_directory_contents("C:/Users/igors/MYWRITE/PKP_new_test", files, &rows, 1);
    if (status) {
        printf("ВНИМАНИЕ! Возникла ошибка при построении каталога файлов!\n");
        free_2d_array_char(files, TEST_TABLE_LEN, 1);
        return 0;
    }

    //Вывод содержимого таблицы файлов
    for (k=0; k<rows; k++)
        printf("%4d) %s\n", k, files[k]);
    
    free_2d_array_char(files, TEST_TABLE_LEN, 1);

    printf("=====================================================\n");

    getch();
    return 0;
}


int list_directory_contents(const char *s_dir, char **files, int *i, int verbose)
{
    char *F_NAME = "list_directory_contents";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    char s_path[2048];
    //Specify a file mask. *.* = We want everything!
    sprintf(s_path, "%s\\*.*", s_dir);

    if((hFind = FindFirstFile(s_path, &fdFile)) == INVALID_HANDLE_VALUE) {
        printf("::%s ->\n\tПуть не найден: %s\n", F_NAME, s_dir);
        return 1;
    }

    do {
        if(strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0) {
            sprintf(s_path, "%s/%s", s_dir, fdFile.cFileName);
            strcpy(files[*i], s_path);
            (*i)++;
        }
    } while(FindNextFile(hFind, &fdFile)); //Find the next file.

    FindClose(hFind); //Always, Always, clean things up!

    return 0;
}


void free_2d_array_char(char** matrix, int rows, int verbose)
{
    char * F_NAME = "free_2d_array_char";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    int i;
    if (verbose)
        printf("::%s ->\n\tОчищаем память под матрицу\n", F_NAME);
    for (i=0; i<rows; i++)
        free((void*) matrix[i]);
    free((void*) matrix);
    if (verbose)
        printf("::%s ->\n\tПамять под матрицу освобождена!\n", F_NAME);
}


/*
Функция для рекрсивного обхода дерева папок

https://stackoverflow.com/questions/2314542/listing-directory-contents-using-c-and-windows
bool ListDirectoryContents(const char *sDir)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    char sPath[2048];

    //Specify a file mask. *.* = We want everything!
    sprintf(sPath, "%s\\*.*", sDir);

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", sDir);
        return false;
    }

    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories.
        if(strcmp(fdFile.cFileName, ".") != 0
                && strcmp(fdFile.cFileName, "..") != 0)
        {
            //Build up our file path using the passed in
            //  [sDir] and the file/foldername we just found:
            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);

            //Is the entity a File or Folder?
            if(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("Directory: %s\n", sPath);
                ListDirectoryContents(sPath); //Recursion, I love it!
            }
            else{
                printf("File: %s\n", sPath);
            }
        }
    }
    while(FindNextFile(hFind, &fdFile)); //Find the next file.

    FindClose(hFind); //Always, Always, clean things up!

    return true;
}

ListDirectoryContents("C:\\Windows\\");
*/