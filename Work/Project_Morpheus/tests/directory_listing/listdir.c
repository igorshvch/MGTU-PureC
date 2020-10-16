#include <stdio.h>
#include <windows.h>

int list_directory_contents(const char *sDir, char **files, int *i);
void free_2d_array_char(char** matrix, int rows);

int main()
{
    int i = 0;
    int j;
    char **files;
    files = (char**) calloc(1000, sizeof(char*));
    for (j=0; j<1000; j++)
        files[j] = (char*) calloc(1000, sizeof(char));
    list_directory_contents("C:/Users/igors/MYWRITE/PKP", files, &i);

    for (j=0; j<i; j++)
        printf("%d) %s\n", j, files[j]);
    
    free_2d_array_char(files, i);

    getch();
    return 0;
}


int list_directory_contents(const char *sDir, char **files, int *i)
{
    char * F_NAME = "list_directory_contents";
    printf("::%s -> вход в функицю\n", F_NAME);

    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    char sPath[2048];

    //Specify a file mask. *.* = We want everything!
    sprintf(sPath, "%s\\*.*", sDir);

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", sDir);
        return 0;
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
            sprintf(sPath, "%s/%s", sDir, fdFile.cFileName);

            //Is the entity a File or Folder?
            /*if(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("Directory: %s\n", sPath);
                ListDirectoryContents(sPath, files, i); //Recursion, I love it!
            }
            else{*/
                //printf("File: %s\n", sPath);
                strcpy(files[*i], sPath);
                (*i)++;
            //}
        }
    }
    while(FindNextFile(hFind, &fdFile)); //Find the next file.

    FindClose(hFind); //Always, Always, clean things up!

    return 1;
}


void free_2d_array_char(char** matrix, int rows)
{
    char * F_NAME = "free_2d_array_char";
    printf("::%s -> вход в функицю\n", F_NAME);

    int i;
    printf("Очищаем память под матрицу\n");
    for (i=0; i<rows; i++)
        free((void*) matrix[i]);
    free((void*) matrix);
    printf("Память под матрицу освобождена!\n");
}