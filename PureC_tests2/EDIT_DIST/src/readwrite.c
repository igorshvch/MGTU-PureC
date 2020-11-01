#include "readwrite.h"


static int main_test()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    printf("=====================================================\n");
    printf("Тест модуля 'readwrite.c'\n");
    printf("=====================================================\n");

    //Объявление перменных
    int i, status, verbose;
    char dir_address[300], output_address[300], *temp_string;
    const char *write_mode;
    EMPT_CHAR_MATRIX file_paths;


    //Инициализация переменных
    verbose = 1;
    write_mode = "a";
    //Инициализация таблицы адресов файлов
    file_paths.max_len = TEST_TABLE_LEN;
    file_paths.table = (char**) calloc(file_paths.max_len, sizeof(char*));
    for (i=0; i<file_paths.max_len; i++)
        file_paths.table[i] = (char*) calloc(file_paths.max_len, sizeof(char*));
    file_paths.rows = 0;

    printf("Введите адрес папки с файлами для копирования:\n");
    scanf("%s", dir_address);
    printf("Вы ввели: %s\n", dir_address);
    printf("Введите адрес файла, в который необходимо скопировать данные:\n");
    scanf("%s", output_address);
    printf("Вы ввели: %s\n", output_address);
    printf("Поиск файлов в папке назначения\n");
    status = list_directory_contents(dir_address, file_paths.table, &(file_paths.rows), verbose);
    if (status) {
        printf("ВНИМАНИЕ! Возникла ошибка при построении каталога файлов!\n");
        free_2d_array_char(file_paths.table, file_paths.max_len, verbose);
        return 0;
    }
    printf("Копирование файлов в итоговый файл\n");
    for (i=0; i<file_paths.rows; i++){
        temp_string = read_from_file(file_paths.table[i], 0);
        status = write_to_file(output_address, temp_string, write_mode, 0);
        free((void*) temp_string);
        if (status) {
            printf("%4d) ВНИМАНИЕ! Возникла ошибка при записи файла:\n%s -> %s\n", i+1, file_paths.table[i], output_address);
            free_2d_array_char(file_paths.table, file_paths.max_len, verbose);
            return 0;
        }
    }

    free_2d_array_char(file_paths.table, file_paths.max_len, verbose);
    printf("=====================================================\n");

    getch();
    return 0;
}


char* read_from_file(char *file_name, int verbose)
{
    char * F_NAME = "read_from_file";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    FILE *input;
    char c;
    char *my_string, *temp;

    int i, j, multiplyer, string_size;

    i = 0;
    multiplyer = 1;
    string_size = CHUNK_SIZE;

    my_string = (char*) calloc(CHUNK_SIZE+1, sizeof(char));
    if((input = fopen(file_name, "r")) == NULL) {
        printf("::%s ->\n\tОшибка при открытии файла!\nFILE: %s\n", F_NAME, file_name);
        return NULL;
    }

    while (1) {
        if ((c=fgetc(input)) == EOF && feof(input))
            break;
        if (i == string_size) {
            string_size = ++multiplyer*CHUNK_SIZE;
            temp = (char*) realloc(my_string, (string_size+1)*sizeof(char));
            if (temp == NULL) {
                printf(
                    "::%s ->\n\tНе удалось выделить память под считываемую строку. Значение мультипликатора: %d\nFILE: %s\n",
                    F_NAME,
                    multiplyer-1,
                    file_name
                );
                break;
            }
            my_string = temp;

        }
        my_string[i] = c;
        i++;
    }
    my_string[i++] = '\0';
    
    fclose(input);

    if (verbose)
        printf(
            "::%s ->\n\tЗначение мультипликатора для строки: %d, выделено ячеек памяти: %d, фактическая длина строки c конечным символом: %d, длина строки: %zd\n",
            F_NAME,
            multiplyer,
            (string_size+1),
            i,
            strlen(my_string)
        );

    temp = (char*) calloc(strlen(my_string)+1, sizeof(char));
    strcpy(temp, my_string);
    free((void*) my_string);
    my_string = temp;

    return my_string;
}


int write_to_file(char *file_name, char *my_string, const char *mode, int verbose)
{
    char * F_NAME = "write_to_file";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    FILE *output;

    if((output = fopen(file_name, mode)) == NULL){
        printf("::%s ->\n\tОшибка при открытии файла!\nFILE: %s\n", F_NAME, file_name);
        return 1;
    }

    fprintf(output,  "%s\n", my_string);
    //fputs(my_string, output);

    fclose(output);
    return 0;
}


int write_to_file_words_table(char *file_name, char **words_table, int table_len, const char *mode, int verbose)
{
    char * F_NAME = "write_to_file_words_table";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    int i;
    FILE *output;

    if((output = fopen(file_name, mode)) == NULL){
        printf("::%s ->\n\tОшибка при открытии файла!\nFILE: %s\n", F_NAME, file_name);
        return 1;
    }

    for (i=0; i<table_len; i++)
        fprintf(output,  "%s\n", words_table[i]);

    fclose(output);
    return 0;
}


int test_raw_copy(char *input_f_name, char *output_f_name, int verbose)
{
    char * F_NAME = "test_copy";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    int i=0;
    char c='0';
    FILE *input, *output;

    if((input = fopen(input_f_name, "r")) == NULL){
        printf("::%s ->\n\tОшибка при открытии файла!\nFILE: %s\n", F_NAME, input_f_name);;
        return 1;
    }
    if((output = fopen(output_f_name, "w")) == NULL){
        printf("::%s ->\n\tОшибка при открытии файла!\nFILE: %s\n", F_NAME, output_f_name);;
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


void test_copy(char *input_f_name, char *output_f_name, int verbose)
{
    char * F_NAME = "test_copy";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);
    
    char *str;

    str = read_from_file(input_f_name, verbose);
    write_to_file(output_f_name, str, "w", verbose);
}