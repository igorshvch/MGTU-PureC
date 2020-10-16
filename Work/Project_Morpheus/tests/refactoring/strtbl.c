#include "readwrite.h"
#include "strtbl.h"


static int main_test()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    printf("=====================================================\n");
    printf("���� ������ 'strtbl.c'\n");
    printf("=====================================================\n");

    //���������� ����������
    int i, status, verbose;
    char dir_address[300], output_address[300], *temp_string;
    const char *write_mode;
    EMPT_CHAR_MATRIX *wrd_tbl, file_paths;

    //������������� ����������
    verbose = 1;
    write_mode = "a";
    //������������� ������� ������� ������
    file_paths.max_len = TEST_TABLE_LEN;
    file_paths.table = (char**) calloc(file_paths.max_len, sizeof(char*));
    for (i=0; i<file_paths.max_len; i++)
        file_paths.table[i] = (char*) calloc(file_paths.max_len, sizeof(char*));
    file_paths.rows = 0;
    //������������� ������� ����
    wrd_tbl = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl->table = (char**) calloc(wrd_tbl->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl->max_len; i++)
        wrd_tbl->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl->rows = 0;
    
    printf("������� ����� ����� � ������� ��� ���������:\n");
    scanf("%s", dir_address);
    printf("�� �����: %s\n", dir_address);
    printf("������� ����� �����, � ������� ���������� ����������� ������:\n");
    scanf("%s", output_address);
    printf("�� �����: %s\n", output_address);
    status = list_directory_contents(dir_address, file_paths.table, &(file_paths.rows), verbose);
    if (status) {
        printf("��������! �������� ������ ��� ���������� �������� ������!\n");
        free_2d_array_char(file_paths.table, file_paths.max_len, verbose);
        free_2d_array_char(wrd_tbl->table, wrd_tbl->max_len, verbose);
        free((void*) wrd_tbl);
        return 0;
    } 
    for (i=0; i<file_paths.rows; i++){
        temp_string = read_from_file(file_paths.table[i], (!verbose));
        create_string_table(temp_string, wrd_tbl, (!verbose));
        printf("%4d) ���� %s ���������!\n",  i+1, file_paths.table[i]);
        status = write_to_file_words_table(output_address, wrd_tbl->table, wrd_tbl->rows, write_mode, (!verbose));
        if (status) {
            printf("%4d) ��������! �������� ������ ��� ������ ����������� �� �����:\n%s\n", i+1, file_paths.table[i]);
            free_2d_array_char(file_paths.table, file_paths.max_len, verbose);
            free_2d_array_char(wrd_tbl->table, wrd_tbl->max_len, verbose);
            free((void*) wrd_tbl);
            return 0;
        }
        //������� ���������� ��� ����� ��������
        wrd_tbl->rows = 0;
        free((void*) temp_string);
    }

    printf("��� ������� ������ ������� ���� �������\n");
    getch();

    free_2d_array_char(file_paths.table, file_paths.max_len, verbose);
    free_2d_array_char(wrd_tbl->table, wrd_tbl->max_len, verbose);
    free((void*) wrd_tbl);
    free((void*) temp_string);
    
    printf("=====================================================\n");

    getch();
    return 0;
}


void create_string_table(char *my_string, EMPT_CHAR_MATRIX *wrd_tbl, int verbose)
{
    char *F_NAME = "create_string_table";
    if (verbose)
        printf("::%s ->\n\t���� � �������\n", F_NAME);

    int i, row, col, len;
    char c;

    row = col = 0;    
    len = strlen(my_string);
    
    for (i=0, row=0; i<len; i++) {
        c = my_string[i];
        if (c >= '0' && c <= '9' || c >= '�' && c <= '�') {
            while (c >= '0' && c <= '9' || c == '-' || c >= '�' && c <= '�' || c == '@' || c == '#' || c == '/') {//while (c != ' ' && c != '\n' &&  c != '\t') {
                wrd_tbl->table[row][col] = c;
                i++; col++;
                c = my_string[i];
            }
            wrd_tbl->table[row][col] = '\0';
            col = 0;
            row++;
        }
    }
    wrd_tbl->rows = row;
}