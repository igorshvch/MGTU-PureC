#include "miohandler.h"


char *read_name_from_console(bool save_name_flag)
{
    char *fname = "read_name_from_console";

    char c;
    const int MAX_LEN = 100;
    int i = 0;
    char *name;
    char *name_trunkate;

    name = (char*) malloc(sizeof(char)*MAX_LEN);

    c = getchar();
    while (c == '\n' || c == ' ' || c == '\t')
        c = getchar();
    
    while (c != '|')
        {
            name[i] = c;
            i++;
            if (i == (MAX_LEN-1))
                {
                    printf("\nFUNC %s -> ��������� ����� ����� �����. ��� ����� ������� �� 99 ��������\n\n", fname);
                    break;
                }
            c = getchar();
        }
    name[i] = '\0';

    printf("%s������� �����: %s\n", INDENT, name);

    name_trunkate = (char*) malloc(sizeof(char)*(strlen(name)+1));
    strcpy(name_trunkate, name);

    free((void*) name);

    if (save_name_flag)
        if (!lookup(name_trunkate))
            append_name_to_table(name_trunkate);

    return name_trunkate;
}


char *read_defn_from_console()
{
    char *fname = "read_defn_from_console";

    char c;
    const int MAX_LEN = 1000;
    int i(0);
    char *defn;
    char *defn_trunkate;

    defn = (char*) malloc(sizeof(char)*MAX_LEN);

    c = getchar();
    while (c == '\n' || c == ' ' || c == '\t')
        c = getchar();
    
    while (c != '|')
        {
            defn[i] = c;
            i++;
            if (i == (MAX_LEN-1))
                {
                    printf("\nFUNC %s -> ��������� ����� ����� �����������. ����������� ����� ������� �� 999 ��������\n\n", fname);
                    break;
                }
            c = getchar();
        }
    defn[i] = '\0';

    printf("%s������� �����������: %s\n", INDENT, defn);

    defn_trunkate = (char*) malloc(sizeof(char)*(strlen(defn)+1));
    strcpy(defn_trunkate, defn);
    
    free((void*) defn);

    return defn_trunkate;
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

    printf("FUNC %s -> ������� �������� �������", fname);
}


void print_names()
{
    int i;

    printf("\n\t============= ������ �������� =============\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "�����");
    printf("\t-------------------------------------------\n");

    for (i=0; i<table_names.rows; i++)
            printf("\t| %4d |%-34s|\n", i+1, table_names.records[i]);
    
    printf("\t===========================================\n\n");
}


void print_defns()
{
    char *fname = "print_defns";
    int i;

    printf("\n\t============ ������ ����������� ===========\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "�����������");
    printf("\t-------------------------------------------\n");

    nlist *np;

    for (i=0; i<table_names.rows; i++)
        {
            np = lookup(table_names.records[i], false);
            if (np)
                printf("\t| %4d |%-34s\n", i+1, np->defn);
            else
                printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
        }
    printf("\t===========================================\n\n");
}


void print_all_dict_to_console()
{
    char *fname = "print_all_dict_to_console";
    int i;

    printf("\n\t============== ������ ������� =============\n");

    nlist *np;

    for (i=0; i<table_names.rows; i++)
        {
            np = lookup(table_names.records[i], false);
            if (np != NULL)
                {
                    printf("\n>>> %s\n", np->name);
                    printf("%s\n", np->defn);
                }
            else
                printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
        }
    printf("\n\t===========================================\n\n");
}


int compare_names_by_length(const void *name1, const void *name2)             //������� ���������, ������� ����� ������������ �������� ���������� qsort()
{
    char *w1, *w2;

    w1 = (char*) name1;
    w2 = (char*) name2;

    return strlen((char*) w1) - strlen((char*) w2);
}