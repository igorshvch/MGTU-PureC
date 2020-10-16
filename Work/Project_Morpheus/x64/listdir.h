#include <stdio.h>
#include <windows.h>

int list_directory_contents(const char *sDir, char **files, int *i);
void free_2d_array_char(char** matrix, int rows);