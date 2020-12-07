#include "user_input_check.h"

int verify_not_too_long_file(char* str)
{
    if (strlen(str) > (MAX_PATH-1))
        return 1;
    else
        return 0;
}

/*
int verify_not_too_long_dir(char* str)
{
    if (strlen(str) > ((MAX_PATH/2)-1))
        return 1;
    else
        return 0;
}
*/


int verify_only_valid_symbols(char* str)
{
    int i, len;
    char c;

    len = strlen(str);

    for (i=0; i<len; i++) {
        c = str[i];
        if (c=='*' || c=='?' || c=='\"' || c=='<' || c=='>' || c=='|')//(c==':' || c=='*' || c=='?' || c=='\"' || c=='<' || c=='>' || c=='|')
            return 1;
    }
    return 0;
}

int verify_file_path_as_valid(char* str)
{
    DWORD dwAttrib = GetFileAttributes(str);
    
    if (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
        return 0;
    else
        return 1;
}

/*
int verify_dir_path_as_valid(char* str)
{
    DWORD dwAttrib = GetFileAttributes(str);
    
    if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
        return 0;
    else
        return 1;
}
*/

int change_backslash_to_slash(char* str)
{
    int i, len, status;
    char c;

    status = 1;

    len = strlen(str);

    for (i=0; i<len; i++) {
        c = str[i];
        if (c=='\\') {
            str[i] = '/';
            if (status)
                status = 0;
        }
    }
    return status;
}
