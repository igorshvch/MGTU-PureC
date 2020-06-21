#include "miohandler.h"


char *read_str_from_console(nlist **hashtable, bool name_mode_flag, bool save_name_flag, bool format_path_flag)
{
    char *fname = "read_str_from_console";

    char c;
    int MAX_LEN;
    if (name_mode_flag)
        MAX_LEN = 100;
    else
        MAX_LEN = 1000;
    int i = 0;
    char *str;
    char *str_trunkate;

    str = (char*) malloc(sizeof(char)*MAX_LEN);

    c = getchar();
    while (c == '\n' || c == ' ' || c == '\t')
        c = getchar();
    
    while (c != '|')
        {
            str[i] = c;
            i++;
            if (i == (MAX_LEN-1))
                {
                    printf("\nFUNC %s -> ��������� ����� ����� �����. ��� ����� ������� �� %d ��������\n\n", fname, (MAX_LEN-1));
                    break;
                }
            c = getchar();
        }
    str[i] = '\0';

    if(!format_path_flag)
        printf("%s������� ������: %s\n", INDENT, str);

    str_trunkate = (char*) malloc(sizeof(char)*(strlen(str)+1));
    strcpy(str_trunkate, str);

    free((void*) str);

    if (save_name_flag)
        if (!lookup(hashtable, str_trunkate))
            append_name_to_table(str_trunkate);
    
    if (format_path_flag)
        {
            for (i=0; i<strlen(str_trunkate); i++)
                if (str_trunkate[i] == '\\')
                    str_trunkate[i] = '/';
            printf("%s������� ������: %s\n", INDENT, str_trunkate);
        }

    return str_trunkate;
}


void append_name_to_table(char *str)
{
    char *fname = "append_name_to_table";
    
    char **tmp;
    int rows;

    table_names.rows++;
    printf("FUNC %s -> ���������� ����� � ������� �������� ���������: %d\n", fname, table_names.rows);

    tmp = (char**) realloc(table_names.records, sizeof(char*)*table_names.rows);
    if (tmp == NULL)
        {
            printf("\nFUNC %s -> �� �������� �������� ������, ���������� ���������� �������\n\n", fname);
        }
    table_names.records = tmp;
    table_names.records[table_names.rows-1] = str;
    printf("FUNC %s -> ������ '%s' ��������� � ������� ��������\n", fname, str);
}


void delete_name_from_table(char *str)
{
    char *fname = "delete_name_from_table";
     
    int i, j;
    bool found_flag = false;
    char* tmp;

    for (i=0; i<table_names.rows; i++)
            if (strcmp(table_names.records[i], str) == 0)
                {
                    free((void*) table_names.records[i]);
                    found_flag = true;
                    printf("FUNC %s -> ������ '%s' ������� � ������� ��������. ���������� ����� ������: %d\n", fname, str, i);
                    break;
                }
    if (found_flag)
        {
            if (i == 0)
                {   
                    printf("FUNC %s -> ������� ������ �� ������ %d\n", fname, i);
                    for (j=0; j<table_names.rows-1; j++)
                        table_names.records[j] = table_names.records[j+1];
                    free((void*) table_names.records[++j]);
                    printf("FUNC %s -> �������� ������ �������\n", fname);
                }
            else
                {   
                    printf("FUNC %s -> ������� ������ �� ������ %d\n", fname, i);
                    for (j=i; j<(table_names.rows-1); j++)
                        table_names.records[j] = table_names.records[j+1];
                    printf("FUNC %s -> �������� ������ �������\n", fname);
                }
            table_names.rows--;
            printf("FUNC %s -> ������ '%s' ������� �� ������� ��������\n", fname, str);
        }
    else
        printf("FUNC %s -> ������ '%s' �� ������� � ������� ��������\n", fname, str);
}


void delete_table()
{
    char *fname = "delete_table";
    
    int i;

    for(i=0; i<table_names.rows; i++)
        free((void*) table_names.records[i]);
    free((void*) table_names.records);
    
    table_names.rows = 0;

    printf("FUNC %s -> ������� �������� �������\n", fname);
}


void print_names()
{
    char *fname = "print_names";

    int i;
    
    printf("\n\t============= ������ �������� =============\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "�����");
    printf("\t-------------------------------------------\n");

    if (table_names.rows < 20)
        for (i=0; i<table_names.rows; i++)
            printf("\t| %4d |%-34s|\n", i+1, table_names.records[i]);
    else
        {
            printf("FUNC %s -> � ������� ����� 20 �������, ����������� ������ 7 ������ � 7 ���������\n", fname);
            for (i=0; i<7; i++)
                printf("\t| %4d |%-34s|\n", i+1, table_names.records[i]);
            printf("\n\n\t.........\n\n");
            for (i=(table_names.rows-7); i<table_names.rows; i++)
                printf("\t| %4d |%-34s|\n", i+1, table_names.records[i]);
        }

    
    printf("\t===========================================\n\n");
}


void print_defns(nlist **hashtable)
{
    char *fname = "print_defns";
    int i;
    nlist *np;

    printf("\n\t============ ������ ����������� ===========\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "�����������");
    printf("\t-------------------------------------------\n");

    if (table_names.rows < 20)
        {
            for (i=0; i<table_names.rows; i++)
                {
                    np = lookup(hashtable, table_names.records[i], false);
                    if (np)
                        printf("\t| %4d |%-34s\n", i+1, np->defn);
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
        }
    else
        {
            printf("FUNC %s -> � ������� ����� 20 �������, ����������� ������ 7 ������ � 7 ���������\n", fname);
            for (i=0; i<7; i++)
                {
                    np = lookup(hashtable, table_names.records[i], false);
                    if (np != NULL)
                        printf("\t| %4d |%-34s\n", i+1, np->defn);
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
            printf("\n\n\t.........\n\n");
            for (i=(table_names.rows-7); i<table_names.rows; i++)
                {
                    np = lookup(hashtable, table_names.records[i], false);
                    if (np)
                        printf("\t| %4d |%-34s\n", i+1, np->defn);
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
        }
    
    printf("\t===========================================\n\n");
}


void print_all_dict_to_console(nlist **hashtable)
{
    char *fname = "print_all_dict_to_console";
    int i;

    printf("\n\t============== ������ ������� =============\n");

    nlist *np;

    if (table_names.rows < 20)
        {
            for (i=0; i<table_names.rows; i++)
                {
                    np = lookup(hashtable, table_names.records[i], false);
                    if (np != NULL)
                        {
                            printf("\n>>> %s\n", np->name);
                            printf("%s\n", np->defn);
                        }
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
        }
    else
        {
            printf("FUNC %s -> � ������� ����� 20 �������, ����������� ������ 7 ������ � 7 ���������\n", fname);
            for (i=0; i<7; i++)
                {
                    np = lookup(hashtable, table_names.records[i], false);
                    if (np != NULL)
                        {
                            printf("\n>>> %s\n", np->name);
                            printf("%s\n", np->defn);
                        }
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
            printf("\n\n\t.........\n\n");
            for (i=(table_names.rows-7); i<table_names.rows; i++)
                {
                    np = lookup(hashtable, table_names.records[i], false);
                    if (np != NULL)
                        {
                            printf("\n>>> %s\n", np->name);
                            printf("%s\n", np->defn);
                        }
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
        }
    
    printf("\n\t===========================================\n\n");
}


int compare_names_by_length_from_short(const void *name1, const void *name2)             //������� ���������, ������� ����� ������������ �������� ���������� qsort()
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;
                       
    return strlen((char*) *w1) - strlen((char*) *w2);
}


int compare_names_by_length_from_long(const void *name1, const void *name2)             //������� ���������, ������� ����� ������������ �������� ���������� qsort()
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;
                       
    return strlen((char*) *w2) - strlen((char*) *w1);
}


int compare_names_by_alph_from_a(const void *name1, const void *name2)
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;

    return strcmp((char*) *w1, (char*) *w2);
}


int compare_names_by_alph_from_z(const void *name1, const void *name2)
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;

    return strcmp((char*) *w2, (char*) *w1);
}


void sort_names(bool flag_alph, bool flag_order_from_min)
{
    char *fname = "sort_names";

    
    if (flag_alph && flag_order_from_min) 
        {
            qsort((void*) table_names.records, table_names.rows, sizeof(char*), compare_names_by_alph_from_a);
            printf("FUNC %s -> ������� ������������� � ���������� ���������� �������\n", fname);
        }
    else if (flag_alph && (!flag_order_from_min)) 
        {
            qsort((void*) table_names.records, table_names.rows, sizeof(char*), compare_names_by_alph_from_z);
            printf("FUNC %s -> ������� ������������� � ���������� ���������� �������\n", fname);
        }
    else if ((!flag_alph) && flag_order_from_min) 
        {
            qsort((void*) table_names.records, table_names.rows, sizeof(char*), compare_names_by_length_from_short);
            printf("FUNC %s -> ������� ������������� � ������� ����������� ����� �����\n", fname);
        }
    else if ((!flag_alph) && (!flag_order_from_min))
        {
            qsort((void*) table_names.records, table_names.rows, sizeof(char*), compare_names_by_length_from_long);
            printf("FUNC %s -> ������� ������������� � ������� ������� ����� �����\n", fname);
        }
}


int read_from_file(nlist **hashtable, char *file_path)
{
    char *fname = "open_file";
    const int MAX_NAME_LEN = 100;
    const int MAX_DEFN_LEN = 1000;
    int i;
    char c = '0';
    char *name, *defn;
    const bool write_to_dict_print_flag = true;

    FILE *file_pointer(NULL);

    file_pointer = fopen(file_path, "r");

    if (file_pointer == NULL)
        {
            printf("FUNC %s -> �� ������� ������� ���� �� ������ '%s'\n", fname, file_path);
            perror("Error: ");
            clearerr(file_pointer);
            return 1;
        }
    
    printf("FUNC %s -> �������� ����� �� ������ '%s'\n", fname, file_path);
    printf("FUNC %s -> � ������ ����� �������� ������� (�� ����� 99 ��������) � �� ����������� (�� ����� 999 ��������)\n", fname);

    if(feof(file_pointer))
        {
            printf("FUNC %s -> ��������� �� ������ �����, ������� %ld\n", fname, ftell(file_pointer));
        }
    else
        {
            printf("FUNC %s -> ��������� �� �� ������ �����, ������� %ld\n", fname, ftell(file_pointer));
        }

    int count = 0;
    while (!feof(file_pointer))
        {
            printf("iter: %d \n", count);
            count++;
            i = 0;
            name = (char*) malloc(sizeof(char)*MAX_NAME_LEN);
            defn = (char*) malloc(sizeof(char)*MAX_DEFN_LEN);
            if (name && defn)
                printf("FUNC %s -> ��� ������� � ����������� ������� �������� ������\n", fname);
            else
                printf("FUNC %s -> ��� ������� ��� ����������� �� ������� �������� ������\n", fname);
            while (c != '|')
                {
                    c = fgetc(file_pointer);
                    name[i] = c;
                    i++;
                    if (i==98)
                        break;
                }
            name[i] = '\0';
            if (c != '|')
                while (c != '|')
                    c = fgetc(file_pointer);
            printf("FUNC %s -> ������ ������ '%s'\n", fname, name);
            i = 0;
            while (c != '\n')
                {
                    c = fgetc(file_pointer);
                    defn[i] = c;
                    i++;
                    if (i==998)
                        break;
                }
            defn[i] = '\0';
            printf("FUNC %s -> ������� ����������� '%s'\n", fname, defn);
            write_to_dict(hashtable, name, defn, write_to_dict_print_flag);
        }
    
    if (fclose(file_pointer) != EOF)
        printf("FUNC %s -> �������� ����� �� ������ '%s'\n", fname, file_path);
    else
        {
            perror("Error: ");
            clearerr(file_pointer);
        }

    return 0;    
}