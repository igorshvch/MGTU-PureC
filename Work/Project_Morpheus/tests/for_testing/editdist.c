#include "editdist.h"


int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    printf("=====================================================\n");
    printf("Тест модуля 'editdist.c'\n");
    printf("=====================================================\n");

    int mode, verbose;
    char file_path1[300], file_path2[300], directory_assress[300], output_address[300];

    verbose = 1;

    printf("Введите режим тестирования (1 - одиночное сравнение; 2 - сравнение в цикле; 3 - сравнение в цикле с постоянной записью):");
    scanf("%d", &mode);
    printf("Вы ввели номер режима: %d\n", mode);
    if (mode == 1){
        printf("Введите адрес первого файла:\n");
        scanf("%s", file_path1);
        printf("Введите адрес второго файла:\n");
        scanf("%s", file_path2);
        printf("Введите адрес итогового файла:\n");
        scanf("%s", output_address);
        printf("Вы ввели:\nfile_path1: %s\n", file_path1);
        printf("Вы ввели:\nfile_path2: %s\n", file_path2);
        printf("Вы ввели:\noutput_address: %s\n", output_address);
        test_single_compare(file_path1, file_path2, output_address, verbose);
    } else {
        if (mode != 2 & mode != 3) {
            printf("Введено некорректное значение режима! Завершение программы\n");
            getch();
            return 0;
        }
        printf("Введите адрес директории с файлами для сравнения:\n");
        scanf("%s", directory_assress);
        printf("Введите адрес итогового файла:\n");
        scanf("%s", output_address);
        printf("Вы ввели:\nfile_path1: %s\n", directory_assress);
        printf("Вы ввели:\nfile_path2: %s\n", output_address);
        if (mode == 2)
            compare_cycle(directory_assress, output_address, verbose);
        else if (mode == 3)
            compare_cycle_with_writing(directory_assress, output_address, verbose);
        else
            printf("Уточнить ветвление в пользовательском интерфейсе!");
    }

    printf("=====================================================\n");


    getch();
    return 0;
}


void test_single_compare(char *file_path1, char *file_path2, char *output_address, int verbose)
{
    //Объявление переменных
    int i;
    EMPT_CHAR_MATRIX *wrd_tbl1, *wrd_tbl2;

    //Инициализация переменных
    //Инициализация таблицы слов для файла 1
    wrd_tbl1 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl1->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl1->table = (char**) calloc(wrd_tbl1->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl1->max_len; i++)
        wrd_tbl1->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl1->rows = 0;
    //Инициализация таблицы слов для файла 2
    wrd_tbl2 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl2->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl2->table = (char**) calloc(wrd_tbl2->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl2->max_len; i++)
        wrd_tbl2->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl2->rows = 0;

    compare(file_path1, file_path2, output_address, wrd_tbl1, wrd_tbl2, verbose);    
    
    free_2d_array_char(wrd_tbl1->table, wrd_tbl1->max_len, verbose);
    free_2d_array_char(wrd_tbl2->table, wrd_tbl2->max_len, verbose);
    free((void*) wrd_tbl1);
    free((void*) wrd_tbl2);
}


int compare_cycle(char *directory_path, char *output_file_path, int verbose)
{
    char * F_NAME = "compare_cycle";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    //Объявление переменных
    int i, j, k, l, status, res;
    double proc;
    const char *write_mode;
    char *str1, *str2, *file_path1, *file_path2, *temp_res_holder, temp_string[600];
    EMPT_CHAR_MATRIX file_paths, *wrd_tbl1, *wrd_tbl2;

    //Инициализация переменных
    //Инициализация строки для промежуточного хранения результатов
    temp_res_holder = (char*) calloc(CHUNK_SIZE_OUTPUT, sizeof(char));
    //Инициализация таблицы адресов
    file_paths.max_len = TEST_TABLE_LEN;
    file_paths.table = (char**) calloc(file_paths.max_len, sizeof(char*));
    for (i=0; i<file_paths.max_len; i++)
        file_paths.table[i] = (char*) calloc(file_paths.max_len, sizeof(char*));
    file_paths.rows = 0;
    //Инициализация таблицы слов для файла 1
    wrd_tbl1 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl1->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl1->table = (char**) calloc(wrd_tbl1->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl1->max_len; i++)
        wrd_tbl1->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl1->rows = 0;
    //Инициализация таблицы слов для файла 2
    wrd_tbl2 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl2->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl2->table = (char**) calloc(wrd_tbl2->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl2->max_len; i++)
        wrd_tbl2->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl2->rows = 0;

    //Формирование таблицы адресов файлов
    status = list_directory_contents(directory_path, file_paths.table, &(file_paths.rows), (!verbose));
    if (status) {
        printf("ВНИМАНИЕ! Возникла ошибка при построении каталога файлов!\n");
        free((void*) temp_res_holder);
        free_2d_array_char(file_paths.table, file_paths.max_len, verbose);
        free_2d_array_char(wrd_tbl1->table, wrd_tbl1->max_len, verbose);
        free_2d_array_char(wrd_tbl2->table, wrd_tbl2->max_len, verbose);
        free((void*) wrd_tbl1);
        free((void*) wrd_tbl2);
        return 0;
    }

    //Цикл сравнения
    j = file_paths.rows;
    l = 0;
    for (i=file_paths.rows-1; i>0; i--) {
        file_path1 = file_paths.table[i];
        j--;
        printf("ПРОГОН № %d", file_paths.rows-j);
        for (k=0; k<j; k++) {
            file_path2 = file_paths.table[k];
            str1 = read_from_file(file_path1, (!verbose));
            str2 = read_from_file(file_path2, (!verbose));
            create_string_table(str1, wrd_tbl1, (!verbose));
            create_string_table(str2, wrd_tbl2, (!verbose));
            res = edit_distance_matrix(wrd_tbl1, wrd_tbl2, (!verbose));
            //Вычисление процента соответствия фрагментов
            proc = 1.0 - ((double) res / ((double) (wrd_tbl1->rows > wrd_tbl2->rows ? wrd_tbl1->rows : wrd_tbl2->rows)));
            l += sprintf(temp_string, "%s|%d|%s|%d|%d|%.6f\n", file_path1, wrd_tbl1->rows, file_path2, wrd_tbl2->rows, res, proc);
            strcat(temp_res_holder, temp_string);
            if (l > (CHUNK_SIZE_OUTPUT-5000)) {
                printf("\tЗапись в файл!");
                write_to_file(output_file_path, temp_res_holder, "a", (!verbose));
                free((void*) temp_res_holder);
                temp_res_holder = (char*) calloc(CHUNK_SIZE_OUTPUT, sizeof(char));
                l = 0;
            }
            free((void*) str1);
            free((void*) str2);
        }
        printf("\n");   
    }
    //Записываем в файл остатки результатов
    write_to_file(output_file_path, temp_res_holder, "a", (!verbose));

    //Освобождение памяти
    free((void*) temp_res_holder);
    free_2d_array_char(file_paths.table, file_paths.max_len, (!verbose));
    free_2d_array_char(wrd_tbl1->table, wrd_tbl1->max_len, (!verbose));
    free_2d_array_char(wrd_tbl2->table, wrd_tbl2->max_len, (!verbose));
    free((void*) wrd_tbl1);
    free((void*) wrd_tbl2);
    return 0;
}


int compare_cycle_with_writing(char *directory_path, char *output_file_path, int verbose)
{
    char * F_NAME = "compare_cycle_with_writing";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    //Объявление переменных
    FILE *output;
    int i, j, k, status, res; //,l ;
    double proc;
    const char *write_mode;
    char *str1, *str2, *file_path1, *file_path2;
    EMPT_CHAR_MATRIX file_paths, *wrd_tbl1, *wrd_tbl2;

    //Инициализация переменных
    //Инициализация таблицы адресов
    file_paths.max_len = TEST_TABLE_LEN;
    file_paths.table = (char**) calloc(file_paths.max_len, sizeof(char*));
    for (i=0; i<file_paths.max_len; i++)
        file_paths.table[i] = (char*) calloc(file_paths.max_len, sizeof(char*));
    file_paths.rows = 0;
    //Инициализация таблицы слов для файла 1
    wrd_tbl1 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl1->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl1->table = (char**) calloc(wrd_tbl1->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl1->max_len; i++)
        wrd_tbl1->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl1->rows = 0;
    //Инициализация таблицы слов для файла 2
    wrd_tbl2 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl2->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl2->table = (char**) calloc(wrd_tbl2->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl2->max_len; i++)
        wrd_tbl2->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl2->rows = 0;

    //Формирование таблицы адресов файлов
    status = list_directory_contents(directory_path, file_paths.table, &(file_paths.rows), (!verbose));
    if (status) {
        printf("ВНИМАНИЕ! Возникла ошибка при построении каталога файлов!\n");
        free_2d_array_char(file_paths.table, file_paths.max_len, verbose);
        free_2d_array_char(wrd_tbl1->table, wrd_tbl1->max_len, verbose);
        free_2d_array_char(wrd_tbl2->table, wrd_tbl2->max_len, verbose);
        free((void*) wrd_tbl1);
        free((void*) wrd_tbl2);
        return 0;
    }

    if((output = fopen(output_file_path, "w")) == NULL){
        printf("::%s ->\n\tОшибка при открытии файла!\nFILE: %s\n", F_NAME, output_file_path);
        return 1;
    }
    //Цикл сравнения
    j = file_paths.rows;
    for (i=file_paths.rows-1; i>0; i--) {
        file_path1 = file_paths.table[i];
        j--;  
        for (k=0; k<j; k++) {
            file_path2 = file_paths.table[k];
            str1 = read_from_file(file_path1, (!verbose));
            str2 = read_from_file(file_path2, (!verbose));
            create_string_table(str1, wrd_tbl1, (!verbose));
            create_string_table(str2, wrd_tbl2, (!verbose));
            res = edit_distance_matrix(wrd_tbl1, wrd_tbl2, (!verbose));
            proc = 1.0 - ((double) res / ((double) (wrd_tbl1->rows > wrd_tbl2->rows ? wrd_tbl1->rows : wrd_tbl2->rows)));
            fprintf(output,  "%s|%d|%s|%d|%d|%.6f\n", file_path1, wrd_tbl1->rows, file_path2, wrd_tbl2->rows, res, proc);
            free((void*) str1);
            free((void*) str2);
        }
        printf("ПРОГОН № %d\n", file_paths.rows-j);
    }
    fclose(output);

    free_2d_array_char(file_paths.table, file_paths.max_len, (!verbose));
    free_2d_array_char(wrd_tbl1->table, wrd_tbl1->max_len, (!verbose));
    free_2d_array_char(wrd_tbl2->table, wrd_tbl2->max_len, (!verbose));
    free((void*) wrd_tbl1);
    free((void*) wrd_tbl2);
    return 0;
}


//__declspec(dllexport) void compare(char *file_path1, char *file_path2, char *output_file_path)
void compare(char *file_path1, char *file_path2, char *output_file_path, EMPT_CHAR_MATRIX* wt1, EMPT_CHAR_MATRIX* wt2, int verbose)
{
    char * F_NAME = "compare";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);
    
    //Объявление переменных
    int res;
    double proc;
    char *str1, *str2, output[OUTPUT_STR_LEN];

    //Инициализация переменных
    str1 = read_from_file(file_path1, verbose);
    str2 = read_from_file(file_path2, verbose);

    create_string_table(str1, wt1, verbose);
    create_string_table(str2, wt2, verbose);

    res = edit_distance_matrix(wt1, wt2, verbose);

    proc = 1.0 - ((double) res / ((double) (wt1->rows > wt2->rows ? wt1->rows : wt2->rows)));
    sprintf(output, "%s|%d|%s|%d|%d|%.6f", file_path1, wt1->rows, file_path2, wt2->rows, res, proc);
    write_to_file(output_file_path, output, "w", verbose);

    free((void*) str1);
    free((void*) str2);
}


int edit_distance_matrix(EMPT_CHAR_MATRIX* wt1, EMPT_CHAR_MATRIX* wt2, int verbose)
{
    char *F_NAME = "edit_distance_matrix";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    int x_coord, y_coord, res, **matrix;
    
    matrix = create_matrix(wt1->rows+1, wt2->rows+1, verbose);
    
    for (x_coord = 1; x_coord <= wt1->rows; x_coord++)
        matrix[x_coord][0] = matrix[x_coord-1][0] + 1;
    for (y_coord = 1; y_coord <= wt2->rows; y_coord++)
        matrix[0][y_coord] = matrix[0][y_coord-1] + 1;

    if (wt1->rows == 0)
        return wt2->rows;
    if (wt2->rows == 0)
        return wt1->rows;

    for (x_coord = 1; x_coord <= wt1->rows; x_coord++)
        for (y_coord = 1; y_coord <= wt2->rows; y_coord++)
            matrix[x_coord][y_coord] = MIN_3_VAL(
                matrix[x_coord-1][y_coord] + 1,
                matrix[x_coord][y_coord-1] + 1,
                matrix[x_coord-1][y_coord-1] + ((strcmp(wt1->table[x_coord], wt2->table[y_coord]) == 0) ? 0 : 1)
            );

    res = matrix[wt1->rows][wt2->rows];

    free_2d_array_int(matrix, wt1->rows+1, verbose);

    return res;
}


int** create_matrix(int rows, int cols, int verbose)
{
    char * F_NAME = "create_matrix";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);

    int row;
    int **matrix;

    matrix = (int**) calloc(rows, sizeof(int));
    for (row = 0; row < rows; row++)
        matrix[row] = (int*) calloc(cols, sizeof(int));
    matrix[0][0] = 0;

    return matrix;
}


void free_2d_array_int(int** matrix, int rows, int verbose)
{
    char * F_NAME = "free_2d_array_int";
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