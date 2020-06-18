#include "miohandler.h"


char *read_name_from_console()
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
                    printf("\nFUNC %s -> достигнут лимит длины имени. Имя будет усечено до 99 символов\n\n", fname);
                    break;
                }
            c = getchar();
        }
    name[i] = '\0';

    printf("%sВведено слово: %s\n", INDENT, name);

    name_trunkate = (char*) malloc(sizeof(char)*(strlen(name)+1));
    strcpy(name_trunkate, name);

    free((void*) name);

    if (!lookup(name_trunkate))
        table_names = append_str_to_table(table_names, name_trunkate);

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
                    printf("\nFUNC %s -> достигнут лимит длины определения. Определение будет усечено до 999 символов\n\n", fname);
                    break;
                }
            c = getchar();
        }
    defn[i] = '\0';

    printf("%sВведено определение: %s\n", INDENT, defn);

    defn_trunkate = (char*) malloc(sizeof(char)*(strlen(defn)+1));
    strcpy(defn_trunkate, defn);
    
    free((void*) defn);

    return defn_trunkate;
}


str_table append_str_to_table(str_table table, char *str)
{
    char *fname = "append_str_to_table";
    char **tmp;
    int rows;

    printf("FUNC %s -> начало выполнения функции\n", fname);
    table.rows++;
    printf("FUNC %s -> количество строк в таблице увеличено: %d\n", fname, table.rows);

    tmp = (char**) realloc(table.records, sizeof(char*)*table.rows);
    if (tmp == NULL)
        {
            printf("\nFUNC %s -> не удалость выделить память, завершение выполнения функции\n\n", fname);
        }
    table.records = tmp;
    table.records[table.rows-1] = str;
    printf("FUNC %s -> запись '%s' добавлена в таблицу\n", fname, str);

    return table;
}


void print_names()
{
    int i;

    printf("\n\t============= Печать терминов =============\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "Слова");
    printf("\t-------------------------------------------\n");

    for (i=0; i<table_names.rows; i++)
            printf("\t| %4d |%-34s|\n", i+1, table_names.records[i]);
    
    printf("\t===========================================\n\n");
}


void print_defns()
{
    char *fname = "print_defns";
    int i;

    printf("\n\t============ Печать определений ===========\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "Определения");
    printf("\t-------------------------------------------\n");

    nlist *np;

    for (i=0; i<table_names.rows; i++)
        {
            np = lookup(table_names.records[i], false);
            if (np)
                printf("\t| %4d |%-34s\n", i+1, np->defn);
            else
                printf("FUNC %s -> ошибка в поиске определения, слово № %d: %s", fname, i, np->name);
        }
}


void print_all_dict_to_console()
{
    char *fname = "print_all_dict_to_console";
    int i;

    printf("\n\t============== Печать словаря =============\n");

    nlist *np;

    for (i=0; i<table_names.rows; i++)
        {
            np = lookup(table_names.records[i], false);
            if (np)
                {
                    printf("\n>>> %s\n", np->name);
                    printf("%s\n", np->defn);
                }
            else
                printf("FUNC %s -> ошибка в поиске определения, слово № %d: %s", fname, i, np->name);
        }
}