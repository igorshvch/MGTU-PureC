#include "mfuncs.h"


char *read_str_from_console(struct nlist **hashtable, struct str_table *table_names, bool name_mode_flag, bool save_name_flag, bool format_path_flag)
/*
������� ���������� ����� �� �������. ���������� �� ���������� ��������, �����������, � ����� ���������� ���� � ������ ������ � ����������.
���������� ����� ��������� ������ '|'
*/
{
    char *fname = "read_str_from_console";

    char c;
    int MAX_LEN;        //������������ ����� �������� ������; ��� ������� - 99 ��������, ��� ����������� ��� ���� � ����� - 999
    if (name_mode_flag)
        MAX_LEN = 100;
    else
        MAX_LEN = 1000;
    int i = 0;
    char *str;
    char *str_trunkate;

    str = (char*) malloc(sizeof(char)*MAX_LEN); // �������� ������ ��� ������ �����

    c = getchar();     //������� ��������� � ������ ����� ���������� �������
    while (c == '\n' || c == ' ' || c == '\t')
        c = getchar();
    
    while (c != '|') //���� ������ �����
        {
            if (c == '\n' || c == '\t') //�������� ��������� � ������ ����� ������ �� �������
                str[i] = ' ';
            else
                str[i] = c;
            i++;
            if (i == (MAX_LEN-1)) //���� ����� ����� ��������� ������������ ����� ������, ������� �� �����. ����� �������� ������ ����� �����, ������������� � ������
                {
                    printf("\nFUNC %s -> ��������� ����� ����� �����. ��� ����� ������� �� %d ��������\n\n", fname, (MAX_LEN-1));
                    break;
                }
            c = getchar();
        }
    str[i] = '\0';

    if(!format_path_flag)
        printf("%s������� ������: %s\n", INDENT, str);

    if (i < MAX_LEN) //���������� ����� �������� � ������ ������ �� ����������� ����� �����
        {
            str_trunkate = (char*) malloc(sizeof(char)*(strlen(str)+1));
            strcpy(str_trunkate, str);
        }

    free((void*) str); //����������� ������ ��-��� ������������� ������

    if (save_name_flag) //���� �������� ������, �� ��������� ��� � ������� ��������
        if (!lookup(hashtable, str_trunkate))
            append_name_to_table(table_names, str_trunkate);
    
    if (format_path_flag) //���� �������� ���� � �����, ������� ��� ������� '\' �� '/'
        {
            for (i=0; i<strlen(str_trunkate); i++)
                if (str_trunkate[i] == '\\')
                    str_trunkate[i] = '/';
            printf("%s������� ������: %s\n", INDENT, str_trunkate);
        }

    return str_trunkate;
}


void append_name_to_table(struct str_table *table_names, char *str, bool print_flag)
/*
���������� ������� � ������� �������� (��������� ������������ ������). �� ���� ������� ������������ ���������� ��������.
*/
{
    char *fname = "append_name_to_table";
    
    char **tmp;
    char *tmp_str;
    int rows;

    (*table_names).rows++;
    if (print_flag)
        printf("FUNC %s -> ���������� ����� � ������� �������� ���������: %d\n", fname, (*table_names).rows);

    tmp = (char**) realloc((*table_names).records, sizeof(char*)*(*table_names).rows); //�������� ������ ��� ������� ������� �������, ���������� ������ �� ������
    if (!tmp)
        {
            printf("\nFUNC %s -> �� �������� �������� ������ ��� ���������, ���������� ���������� �������\n\n", fname);
        }
    (*table_names).records = tmp;

    tmp_str = (char*) malloc(sizeof(char)*strlen(str)+1);   //�������� ������ ��� �����
    if (!tmp_str)
        {
            printf("\nFUNC %s -> �� �������� �������� ������ ��� ������, ���������� ���������� �������\n\n", fname);

        }
    (*table_names).records[(*table_names).rows-1] = strcpy(tmp_str, str); //���������� ������ � �������
    if (print_flag)
        printf("FUNC %s -> ������ '%s' ��������� � ������� ��������\n", fname, str);
}


void delete_name_from_table(struct str_table *table_names, char *str)
/*
�������� ������� �� ������� ��������. �������� ��� ��������:
1) ��������� ������ �� ����� ������;
2) ��������� ��������� �� ����� ������ (������ ����� n);
3) ��������� �����-���� �� �������� �� ������� �� n-1.
������ � ������ ������ ����� ����������� ����� ����������
*/
{
    char *fname = "delete_name_from_table";
     
    int i, j;
    bool found_flag = false;
    char* tmp;

    for (i=0; i<(*table_names).rows; i++)                       //����� ������� ������� � �������
            if (strcmp((*table_names).records[i], str) == 0)
                {
                    free((void*) (*table_names).records[i]);    //������� �������� ������
                    found_flag = true;
                    printf("FUNC %s -> ������ '%s' ������� � ������� ��������. ���������� ����� ������: %d\n", fname, str, i);
                    break;
                }
    if (found_flag)
        {
            printf("FUNC %s -> ������� ������ �� ������ %d\n", fname, i);
            if (i == 0) //���� ��������� ������ ������, �������� ������� � ������������
                {   
                    for (j=0; j<(*table_names).rows-1; j++)
                        (*table_names).records[j] = (*table_names).records[j+1];
                }
            else    //���� ��������� ������ �� �������� ��� ����� �������, �������� ������� � ������������
                {   
                    for (j=i; j<((*table_names).rows-1); j++)
                        (*table_names).records[j] = (*table_names).records[j+1];
                }
            //j++;
            printf("FUNC %s -> ����������� ������ �� ������ %d\n", fname, j);
            free((void*) (*table_names).records[j]);
            printf("FUNC %s -> �������� ������ �������\n", fname);
            (*table_names).rows--;
            printf("FUNC %s -> ������ '%s' ������� �� ������� ��������\n", fname, str);
        }
    else
        printf("FUNC %s -> ������ '%s' �� ������� � ������� ��������\n", fname, str);
}


void delete_table(struct str_table *table_names)
/*
�������� ������� ��������
*/
{
    char *fname = "delete_table";
    
    int i;

    for(i=0; i<(*table_names).rows; i++)
        free((void*) (*table_names).records[i]);
    free((void*) (*table_names).records);
    
    (*table_names).rows=0;

    free((void*) table_names);

    printf("FUNC %s -> ������� �������� ������� �� ������\n", fname);
}


void print_names(struct str_table *table_names)
/*
������ � ������� ��������. ���� �������� ������ 10. �� ����� ����������� 9 ������
� 9 ���������. ���� ������������� �������, �� ������� ������ � ���������� � ���� ����������� ����� ����� �������.
*/
{
    char *fname = "print_names";
    const int BORDER = 20;
    const int PRINT_NUM = 9;

    int i;
    
    if ((*table_names).rows > BORDER)
        printf("FUNC %s -> � ������� ����� %d �������, ����������� ������ %d ������ � %d ���������\n", fname, BORDER, PRINT_NUM, PRINT_NUM);
    
    printf("\n\t============= ������ �������� =============\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "�����");
    printf("\t-------------------------------------------\n");

    if ((*table_names).rows < BORDER+1)
        for (i=0; i<(*table_names).rows; i++)
            printf("\t| %4d |%-34s|\n", i+1, (*table_names).records[i]);
    else
        {
            for (i=0; i<PRINT_NUM; i++)
                printf("\t| %4d |%-34s|\n", i+1, (*table_names).records[i]);
            printf("\n\t.........\n\n");
            for (i=((*table_names).rows-PRINT_NUM); i<(*table_names).rows; i++)
                printf("\t| %4d |%-34s|\n", i+1, (*table_names).records[i]);
        }

    
    printf("\t===========================================\n\n");
}


void print_defns(struct nlist **hashtable, struct str_table *table_names)
/*
������ � ������� �����������. ���� ����������� ������ 10. �� ����� ����������� 9 ������
� 9 ���������. ���� ������������� �������, �� ������� ������ � ���������� � ���� ����������� ����� ����� �������,
�.�. �� ������ � ���������� ������� �� ������� �������� � ������� ��������.
*/
{
    char *fname = "print_defns";
    int i;
    const int BORDER = 20;
    const int PRINT_NUM = 9;
    struct nlist *np;

    if ((*table_names).rows > BORDER)
        printf("FUNC %s -> � ������� ����� %d �������, ����������� ������ %d ������ � %d ���������\n", fname, BORDER, PRINT_NUM, PRINT_NUM);

    printf("\n\t============ ������ ����������� ===========\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "�����������");
    printf("\t-------------------------------------------\n");

    if ((*table_names).rows < BORDER+1)
        {
            
            for (i=0; i<(*table_names).rows; i++)
                {
                    np = lookup(hashtable, (*table_names).records[i], false);
                    if (np)
                        printf("\t| %4d |%-34s\n", i+1, np->defn);
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
        }
    else
        {
            for (i=0; i<PRINT_NUM; i++)
                {
                    np = lookup(hashtable, (*table_names).records[i], false);
                    if (np != NULL)
                        printf("\t| %4d |%-34s\n", i+1, np->defn);
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
            printf("\n\t.........\n\n");
            for (i=((*table_names).rows-PRINT_NUM); i<(*table_names).rows; i++)
                {
                    np = lookup(hashtable, (*table_names).records[i], false);
                    if (np)
                        printf("\t| %4d |%-34s\n", i+1, np->defn);
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
        }
    
    printf("\t===========================================\n\n");
}


void print_all_dict_to_console(struct nlist **hashtable, struct str_table *table_names)
/*
������ ������� � �������. ���� � ������� ����� 20 ��������, �� ���������� ������ 9 � ��������� 9.
��������� ������� ����� ����������� � ����
*/
{
    char *fname = "print_all_dict_to_console";
    int i;
    const int BORDER = 20;
    const int PRINT_NUM = 9;

    struct nlist *np;

    if ((*table_names).rows > BORDER)
        printf("FUNC %s -> � ������� ����� %d �������, ����������� ������ %d ������ � %d ���������\n", fname, BORDER, PRINT_NUM, PRINT_NUM);
    
    printf("\n\t============== ������ ������� =============\n");

    if ((*table_names).rows < BORDER+1)
        {
            for (i=0; i<(*table_names).rows; i++)
                {
                    np = lookup(hashtable, (*table_names).records[i], false);
                    if (np != NULL)
                        {
                            printf("\n>>> %s\n", np->name);
                            printf("%s <<<\n", np->defn);
                        }
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
        }
    else
        {
            for (i=0; i<PRINT_NUM; i++)
                {
                    np = lookup(hashtable, (*table_names).records[i], false);
                    if (np != NULL)
                        {
                            printf("\n>>> %s\n", np->name);
                            printf("%s <<<\n", np->defn);
                        }
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
            printf("\n\t......................................................\n");
            for (i=((*table_names).rows-PRINT_NUM); i<(*table_names).rows; i++)
                {
                    np = lookup(hashtable, (*table_names).records[i], false);
                    if (np != NULL)
                        {
                            printf("\n>>> %s\n", np->name);
                            printf("%s <<<\n", np->defn);
                        }
                    else
                        printf("FUNC %s -> ������ � ������ �����������, ����� � %d: %s", fname, i, np->name);
                }
        }
    
    printf("\n\t===========================================\n\n");
}


int compare_names_by_length_from_short(const void *name1, const void *name2)
/*
������� ��������� �� ����� ����� (�� �������� � �������)
*/
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;
                       
    return strlen((char*) *w1) - strlen((char*) *w2);
}


int compare_names_by_length_from_long(const void *name1, const void *name2)
/*
������� ��������� �� ����� ����� (�� ������� � ��������)
*/
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;
                       
    return strlen((char*) *w2) - strlen((char*) *w1);
}


int compare_names_by_alph_from_a(const void *name1, const void *name2)
/*
������� ��������� �� ����������� ������� (�� � �� �)
*/
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;

    return strcmp((char*) *w1, (char*) *w2);
}


int compare_names_by_alph_from_z(const void *name1, const void *name2)
/*
������� ��������� �� ����������� ������� (�� � �� �)
*/
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;

    return strcmp((char*) *w2, (char*) *w1);
}


void sort_names(struct str_table *table_names, bool flag_alph, bool flag_order_from_min)
/*
������� ����������. ������� ����������� �� ��������. ����� ������������� � ����������
(���������� � ���������� �������), � ����� �� ����� ������� (�� ����������� ��� �� ��������).
���� ������������� �������, �� ��� �������� �� ������� ������ �����������,
� ����� �� ������� ���������� ��������� ������� � ����.
*/
{
    char *fname = "sort_names";

    
    if (flag_alph && flag_order_from_min) 
        {
            qsort((void*) (*table_names).records, (*table_names).rows, sizeof(char*), compare_names_by_alph_from_a);
            printf("FUNC %s -> ������� ������������� � ���������� ���������� �������\n", fname);
        }
    else if (flag_alph && (!flag_order_from_min)) 
        {
            qsort((void*) (*table_names).records, (*table_names).rows, sizeof(char*), compare_names_by_alph_from_z);
            printf("FUNC %s -> ������� ������������� � ���������� ���������� �������\n", fname);
        }
    else if ((!flag_alph) && flag_order_from_min) 
        {
            qsort((void*) (*table_names).records, (*table_names).rows, sizeof(char*), compare_names_by_length_from_short);
            printf("FUNC %s -> ������� ������������� � ������� ����������� ����� �����\n", fname);
        }
    else if ((!flag_alph) && (!flag_order_from_min))
        {
            qsort((void*) (*table_names).records, (*table_names).rows, sizeof(char*), compare_names_by_length_from_long);
            printf("FUNC %s -> ������� ������������� � ������� ������� ����� �����\n", fname);
        }
}


int read_from_file(struct nlist **hashtable, struct str_table *table_names, char *file_path, bool print_flag)
/*
������� ��������� ��������������� ������ ���� <������>|<�����������>\n.
��� ���� � ���� ����������� ����� ��������� ����� '|', ��� �� ����� 
��������� ���������� �������, ������� ��������� ������ �����.
� ������ ������ ������� �� �����-���� ������, ������ ������������,
��������� ������ ������� � ������
*/
{
    char *fname = "read_from_file";
    const int MAX_NAME_LEN = 100;
    const int MAX_DEFN_LEN = 1000;
    int i;
    char c = '0';
    char *name, *defn;
    const bool write_to_dict_print_flag = print_flag;
    const bool append_name_to_table_print_flag = print_flag;

    FILE *file_pointer(NULL);

    file_pointer = fopen(file_path, "r");

    if (file_pointer == NULL)
        {
            perror("Error: ");
            clearerr(file_pointer);
            return -1;
        }
    
    printf("FUNC %s -> �������� ����� �� ������ '%s'\n", fname, file_path);
    printf("FUNC %s -> � ������ ����� �������� ������� (�� ����� 99 ��������) � �� ����������� (�� ����� 999 ��������)\n", fname);

    int count = 0;
    while (!feof(file_pointer))
        {
            if (print_flag)
                {
                    printf("iter: %d \n", count);
                    count++;
                }
            i = 0;
            name = (char*) malloc(sizeof(char)*MAX_NAME_LEN);
            defn = (char*) malloc(sizeof(char)*MAX_DEFN_LEN);
            while (true)                            //���� ������ �������
            /*
            �� ����� ������ ������� ����� ���� ��� ������:
            1) ��� ���������� ��������������� ������� | (��� ����������� �������, �� ��������� �������������� ���������);
            2) ��� ���������� ����� �����;
            3) ��� ���������� ������� ����� ������ (��������������, ��� ������ ��� ����������� �� ������������� ��������� �������),
            4) ��� ���������� ������� ����� ������� (99 ��������)
            */
                {
                    c = fgetc(file_pointer);
                    if (c == '|' || feof(file_pointer) || c == '\n') //����������� ������ ������� � ������� 1-3
                        {
                            i++;
                            break;
                        }
                    if (c == '\t')                                   //�������� �������� �� ������
                        name[i] = ' ';
                    else
                        name[i] = c;
                    i++;
                    if (i==99)                                       //����������� ������ ������� � ������ 4
                        break;
                }
            name[i] = '\0';
            if (c != '|')
            /*
            ���� ��������� ������ ����� ������ (������ 4), ���������� ������ ������� ���� �� ������ �� �����������, ���� ����� ������, ���� ����� �����.
            � ��������� ���� ������� �������, ��� ������ �������, ���������� ������ �����, ������� ������ ������
            */
                while (c != '|')
                    {
                        c = fgetc(file_pointer);
                        if (feof(file_pointer) || c == '\n')
                            break;
                    }
            if (feof(file_pointer) || c == '\n')    //���� ��������� ����� ����� ��� ����� ������ (������ 2 � 3), �� ������ �������, ���������� ������ �����, ����������� ������ ������
                {
                    free((void*) name);
                    free((void*) defn);
                    break;
                }
                    
            if (print_flag)
                printf("FUNC %s -> ������ ������ '%s'\n", fname, name);
            i = 0;
            while (true)                            //���� ������ �����������
            /*
            �� ����� ������ ����������� ����� ���� ��� �������� ������:
            1) ��������� ������ ����� ������ (��� ����������� �������);
            2) ��������� ����� ����� (��� ����� ����� ���� ����������� ���������, �� ��������� �������������� ���������);
            3) ��������� ����� ����� ������ ��� �����������
            */
                {
                    c = fgetc(file_pointer);
                    if (c == '\n' || feof(file_pointer)) //����� �� ����� �� �������� 1 ��� 2
                        {
                            i++;
                            break;
                        }
                    defn[i] = c;
                    if (c == '\t')                  //�������� ������ ��������� �� ������
                        defn[i] = ' ';
                    else
                        defn[i] = c;
                    i++;
                    if (i==999)                     //������� ������ �� ����� ������ ����������� ��� ���������� ���������� ����� ������ (������ 3)
                        break;
                }
            defn[i] = '\0';
            while (c != '\n' && !feof(file_pointer)) //����� �� ����� ������ ����������� ��������� � ����� � ����������� ����� ������, ���������� �������, ���� �� ������ �� ����� ������ ��� �����, ���� ��� ��������� ������
                c = fgetc(file_pointer);
            
            if (print_flag)
                printf("FUNC %s -> ������� ����������� '%s'\n", fname, defn);
            
            write_to_dict(hashtable, name, defn, write_to_dict_print_flag);             //������ � ������� ������� � �����������
            append_name_to_table(table_names, name, append_name_to_table_print_flag);   //������ ������� � ������� ��������
        }
    
    if (fclose(file_pointer) == EOF)
        {
            perror("Error: ");
            clearerr(file_pointer);
            return -2;
        }
    return 0;    
}


int save_to_file(struct nlist **hashtable, struct str_table *table_names, char *file_path)
/*
������� ������ ������� � ��������� ����. ������ ������ �������: <������>|<�����������>\n.
���� ����������� � ������ 'a+', �� ���� ���������� ������ ��� ������ ����� ���������.
*/
{
    char *fname = "save_to_file";
    int i;
    long int il_s, il_e;
    char *name, *defn;
    struct nlist *np;

    FILE *file_pointer(NULL);

    file_pointer = fopen(file_path, "a+");

    if (file_pointer == NULL)
        {
            perror("Error: ");
            clearerr(file_pointer);
            return -1;
        }
    
    printf("FUNC %s -> �������� ����� �� ������ '%s'\n", fname, file_path);
    printf("FUNC %s -> � ���� ����� �������� ������� � ����������� ����� �������������� ������ '|'\n", fname);

    fseek(file_pointer, 0l, SEEK_SET); //���� ���� �� ������, ��������� ������ ����� ������
    il_s = ftell(file_pointer);
    fseek(file_pointer, 0l, SEEK_END);
    il_e = ftell(file_pointer);
    if (il_s != il_e)
        {
            printf("FUNC %s -> � �������� ����� ��� ���� ������, ��������� ������ ����� ������ ('\\n')\n", fname);
            fputs("\n", file_pointer);
        }

    for (i=0; i<(*table_names).rows; i++)   //���� ������ ������ �������� �������: <������>|<�����������>\n.
        {
            np = lookup(hashtable, (*table_names).records[i], false);
            fputs((*table_names).records[i], file_pointer);
            fputs("|", file_pointer);
            fputs(np->defn, file_pointer);
            if (i != (*table_names).rows-1)
                fputs("\n", file_pointer);
        }
    
    if (fclose(file_pointer) == EOF)
        {
            perror("Error: ");
            clearerr(file_pointer);
            return -2;
        }
    
    return 0;
}