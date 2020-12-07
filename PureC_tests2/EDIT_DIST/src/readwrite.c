#include "readwrite.h"

char* read_from_file(int test_mode, FILE *input, char *stream, char *file_name)
{
    int c, i, j;
    char *my_string;

    if (!test_mode) {
        input = fopen(file_name, "r");
    }

    i = 0;
    my_string = (char*) calloc(CHUNK_SIZE, sizeof(char));

    while (i < CHUNK_SIZE-1) {
        if (!test_mode) {
            if ((c=fgetc(input)) == '|')
                break;
        }
        else {
            c = stream[i];
            if (c == '|')
                break;
        }
        my_string[i] = c;
        i++;
    }
    my_string[i++] = c;
    my_string[i] = '\0';
    
    if (!test_mode)
        fclose(input);

    return my_string;
}


char* write_to_file(int test_mode, FILE *output, char *file_name, char *stream,  int res)
{
    if (!test_mode) {
        output = fopen(file_name, "a");
        fprintf(output,  "editorial distance equals to %d\n", res);
        fclose(output);
        return "";
    }
    else {
        sprintf(stream, "editorial distance equals to %d\n", res);
        return stream;
    }
}