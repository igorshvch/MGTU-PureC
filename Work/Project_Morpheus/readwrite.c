#include "readwrite.h"

//#define DLL_PREF __declspec(dllexport)

#define CHUNK_SIZE 100000

char* read_from_file(char *file_name);
int write_to_file(char *file_name, char *my_string);
int write_to_file_append(char *file_name, char *my_string);
int test_copy(char *input_f_name, char *output_f_name);

static int main_test()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    //printf("=====================================================\n");
    //printf("���� ������ 'readwrite.c'\n");
    //printf("=====================================================\n");

    int status;
    char *test_string1, *test_string2;
    test_string1 = "Trying to print something in English!\n� ������ ��������� ���������� ��-������!\n";

    status = write_to_file("test_write.txt", test_string1);
    //printf("������� �������� ������� ���� 'test_write.txt'\n");
    status = test_copy("test_input.txt", "test_output.txt");
    if (!status)
        //printf("������� ����������� �������� ���� 'test_input.txt' � 'test_output.txt'\n");

    test_string2 = read_from_file("test_input.txt");

    write_to_file("test_output2.txt", test_string2);

    free((void*) test_string2);
    //printf("������ ��� ������ �����������\n");

    //printf("=====================================================\n");

    getch();
    return 0;
}


char* read_from_file(char *file_name)
{
    char * F_NAME = "read_from_file";
    //printf("::%s -> ���� � �������\n", F_NAME);

    FILE *input;
    char c;
    char *my_string, *temp;

    int i, j, multiplyer, base_string_size, string_size;

    i = 0;
    multiplyer = 1;
    string_size = base_string_size = CHUNK_SIZE;

    my_string = (char*) calloc(base_string_size+1, sizeof(char));
    if((input = fopen(file_name, "r")) == NULL) {
        //printf("input file error!\n");
        return NULL;
    }

    while (1) {
        if ((c=fgetc(input)) == EOF && feof(input))
            break;
        if (i == string_size) {
            string_size = ++multiplyer*base_string_size;
            temp = (char*) realloc(my_string, (string_size+1)*sizeof(char));
            if (temp == NULL) {
                //printf("�� ������� �������� ������ ��� ����������� ������. �������� ���������������: %d\n", multiplyer-1);
                break;
            }
            my_string = temp;

        }
        my_string[i] = c;
        i++;
    }
    my_string[i++] = '\0';

    //printf("�������� ��������������� ��� ������: %d, �������� ����� ������: %d, ����������� ����� ������ c �������� ��������: %d, ����� ������: %zd\n", multiplyer, (string_size+1), i, strlen(my_string));

    temp = (char*) calloc(strlen(my_string)+1, sizeof(char));
    strcpy(temp, my_string);
    free((void*) my_string);
    my_string = temp;

    fclose(input);

    return my_string;
}


int write_to_file(char *file_name, char *my_string)
{
    char * F_NAME = "write_to_file";
    //printf("::%s -> ���� � �������\n", F_NAME);

    FILE *output;

    if((output = fopen(file_name, "w")) == NULL){
        //printf("Output file error!\n");
        return 1;
    }

    //fprintf(output,  "%s", string);
    fputs(my_string, output);

    fclose(output);
    return 0;
}


int write_to_file_append(char *file_name, char *my_string)
{
    char * F_NAME = "write_to_file_append";
    //printf("::%s -> ���� � �������\n", F_NAME);

    FILE *output;

    if((output = fopen(file_name, "a")) == NULL){
        //printf("Output file error!\n");
        return 1;
    }

    fprintf(output,  "%s", my_string);
    //fputs(my_string, output);

    fclose(output);
    return 0;
}


int test_copy(char *input_f_name, char *output_f_name)
{
    char * F_NAME = "test_copy";
    //printf("::%s -> ���� � �������\n", F_NAME);

    FILE *input, *output;
    char c='0';
    int i=0;

    if((input = fopen(input_f_name, "r")) == NULL){
        //printf("input file error!\n");
        return 1;
    }
    if((output = fopen(output_f_name, "w")) == NULL){
        //printf("Output file error!\n");
        return 2;
    }
    
    while (1) {
        if ((c=fgetc(input)) == EOF && feof(input))
            break;
        fputc(c, output);
    }

    fclose(output);
    fclose(input);

    return 0;
}