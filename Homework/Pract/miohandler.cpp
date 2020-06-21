#include "mfuncs.h"


char *read_str_from_console(struct nlist **hashtable, struct str_table *table_names, bool name_mode_flag, bool save_name_flag, bool format_path_flag)
/*
Функция считывания ввода из консоли. Рассчитана на считывание терминов, определений, а также считывание пути к файлам записи и сохранения.
Окончанием ввода считается символ '|'
*/
{
    char *fname = "read_str_from_console";

    char c;
    int MAX_LEN;        //максимальная длина вводимой строки; для термина - 99 символов, для определения или пути к файлу - 999
    if (name_mode_flag)
        MAX_LEN = 100;
    else
        MAX_LEN = 1000;
    int i = 0;
    char *str;
    char *str_trunkate;

    str = (char*) malloc(sizeof(char)*MAX_LEN); // выделяем память под строку ввода

    c = getchar();     //удаляем следующие в начале ввода пробельные символы
    while (c == '\n' || c == ' ' || c == '\t')
        c = getchar();
    
    while (c != '|') //цикл записи ввода
        {
            if (c == '\n' || c == '\t') //заменяем табуляцию и символ новой строки на пробелы
                str[i] = ' ';
            else
                str[i] = c;
            i++;
            if (i == (MAX_LEN-1)) //если длина ввода превысила максимальнуб длину строки, выходим из цикла. Далее сохраним только часть ввода, уместившегося в строку
                {
                    printf("\nFUNC %s -> достигнут лимит длины имени. Имя будет усечено до %d символов\n\n", fname, (MAX_LEN-1));
                    break;
                }
            c = getchar();
        }
    str[i] = '\0';

    if(!format_path_flag)
        printf("%sВведена строка: %s\n", INDENT, str);

    if (i < MAX_LEN) //уменьшаяем длину хранимой в памяти строки до фактической длины ввода
        {
            str_trunkate = (char*) malloc(sizeof(char)*(strlen(str)+1));
            strcpy(str_trunkate, str);
        }

    free((void*) str); //освобождаем память из-под несокращенной строки

    if (save_name_flag) //если вводился термин, то добавляем его в таблицу терминов
        if (!lookup(hashtable, str_trunkate))
            append_name_to_table(table_names, str_trunkate);
    
    if (format_path_flag) //если вводился путь к файлу, заменим все символы '\' на '/'
        {
            for (i=0; i<strlen(str_trunkate); i++)
                if (str_trunkate[i] == '\\')
                    str_trunkate[i] = '/';
            printf("%sВведена строка: %s\n", INDENT, str_trunkate);
        }

    return str_trunkate;
}


void append_name_to_table(struct str_table *table_names, char *str, bool print_flag)
/*
Добавление термина в таблицу терминов (двумерный динмаический массив). За счет таблицы производится сортировка терминов.
*/
{
    char *fname = "append_name_to_table";
    
    char **tmp;
    char *tmp_str;
    int rows;

    (*table_names).rows++;
    if (print_flag)
        printf("FUNC %s -> количество строк в таблице терминов увеличено: %d\n", fname, (*table_names).rows);

    tmp = (char**) realloc((*table_names).records, sizeof(char*)*(*table_names).rows); //выделяем память под внешний уровень массива, содержащий ссылки на строки
    if (!tmp)
        {
            printf("\nFUNC %s -> не удалость выделить память для указателя, завершение выполнения функции\n\n", fname);
        }
    (*table_names).records = tmp;

    tmp_str = (char*) malloc(sizeof(char)*strlen(str)+1);   //выделяем память для строк
    if (!tmp_str)
        {
            printf("\nFUNC %s -> не удалость выделить память для строки, завершение выполнения функции\n\n", fname);

        }
    (*table_names).records[(*table_names).rows-1] = strcpy(tmp_str, str); //записываем строку в таблицу
    if (print_flag)
        printf("FUNC %s -> запись '%s' добавлена в таблицу терминов\n", fname, str);
}


void delete_name_from_table(struct str_table *table_names, char *str)
/*
Удаление термина из таблицы терминов. Возможны три варианта:
1) удаляется первый по счету термин;
2) удаляется последний по счету термин (термин номер n);
3) удаляется какой-либо из терминов со второго по n-1.
Первый и третий случаи можно представить одним выражением
*/
{
    char *fname = "delete_name_from_table";
     
    int i, j;
    bool found_flag = false;
    char* tmp;

    for (i=0; i<(*table_names).rows; i++)                       //поиск индекса термина в таблице
            if (strcmp((*table_names).records[i], str) == 0)
                {
                    free((void*) (*table_names).records[i]);    //удаляем заданный термин
                    found_flag = true;
                    printf("FUNC %s -> запись '%s' найдена в таблице терминов. Внутренний номер строки: %d\n", fname, str, i);
                    break;
                }
    if (found_flag)
        {
            printf("FUNC %s -> удаляем запись на строке %d\n", fname, i);
            if (i == 0) //если удаляется первый термин, приводим таблицу в соответствие
                {   
                    for (j=0; j<(*table_names).rows-1; j++)
                        (*table_names).records[j] = (*table_names).records[j+1];
                }
            else    //если удаляется термин из середины или конца таблицы, приводим таблицу в соответствие
                {   
                    for (j=i; j<((*table_names).rows-1); j++)
                        (*table_names).records[j] = (*table_names).records[j+1];
                }
            //j++;
            printf("FUNC %s -> освобождаем память на строке %d\n", fname, j);
            free((void*) (*table_names).records[j]);
            printf("FUNC %s -> удаление прошло успешно\n", fname);
            (*table_names).rows--;
            printf("FUNC %s -> запись '%s' удалена из таблицы терминов\n", fname, str);
        }
    else
        printf("FUNC %s -> запись '%s' не найдена в таблице терминов\n", fname, str);
}


void delete_table(struct str_table *table_names)
/*
Удаление таблицы терминов
*/
{
    char *fname = "delete_table";
    
    int i;

    for(i=0; i<(*table_names).rows; i++)
        free((void*) (*table_names).records[i]);
    free((void*) (*table_names).records);
    
    (*table_names).rows=0;

    free((void*) table_names);

    printf("FUNC %s -> таблица терминов удалена из памяти\n", fname);
}


void print_names(struct str_table *table_names)
/*
Печать в консоль терминов. Если терминов больше 10. то будет распечатано 9 первых
и 9 последних. Если отсортировать термины, то порядок печати и сохранения в файл определений будет также изменен.
*/
{
    char *fname = "print_names";
    const int BORDER = 20;
    const int PRINT_NUM = 9;

    int i;
    
    if ((*table_names).rows > BORDER)
        printf("FUNC %s -> В словаре более %d записей, сокращенная печать %d первых и %d последних\n", fname, BORDER, PRINT_NUM, PRINT_NUM);
    
    printf("\n\t============= Печать терминов =============\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "Слова");
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
Печать в консоль определений. Если определений больше 10. то будет распечатано 9 первых
и 9 последних. Если отсортировать термины, то порядок печати и сохранения в файл определений будет также изменен,
т.к. их печать и сохранение зависит от порядка терминов в таблице терминов.
*/
{
    char *fname = "print_defns";
    int i;
    const int BORDER = 20;
    const int PRINT_NUM = 9;
    struct nlist *np;

    if ((*table_names).rows > BORDER)
        printf("FUNC %s -> В словаре более %d записей, сокращенная печать %d первых и %d последних\n", fname, BORDER, PRINT_NUM, PRINT_NUM);

    printf("\n\t============ Печать определений ===========\n");
    printf("\n\t===========================================\n");
    printf("\t| %4s |%-34s|\n", "#", "Определения");
    printf("\t-------------------------------------------\n");

    if ((*table_names).rows < BORDER+1)
        {
            
            for (i=0; i<(*table_names).rows; i++)
                {
                    np = lookup(hashtable, (*table_names).records[i], false);
                    if (np)
                        printf("\t| %4d |%-34s\n", i+1, np->defn);
                    else
                        printf("FUNC %s -> ошибка в поиске определения, слово № %d: %s", fname, i, np->name);
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
                        printf("FUNC %s -> ошибка в поиске определения, слово № %d: %s", fname, i, np->name);
                }
            printf("\n\t.........\n\n");
            for (i=((*table_names).rows-PRINT_NUM); i<(*table_names).rows; i++)
                {
                    np = lookup(hashtable, (*table_names).records[i], false);
                    if (np)
                        printf("\t| %4d |%-34s\n", i+1, np->defn);
                    else
                        printf("FUNC %s -> ошибка в поиске определения, слово № %d: %s", fname, i, np->name);
                }
        }
    
    printf("\t===========================================\n\n");
}


void print_all_dict_to_console(struct nlist **hashtable, struct str_table *table_names)
/*
Печать словаря в консоль. Если в словаре более 20 терминов, то печатаются первые 9 и последние 9.
Полностью словарь можно распечатать в файл
*/
{
    char *fname = "print_all_dict_to_console";
    int i;
    const int BORDER = 20;
    const int PRINT_NUM = 9;

    struct nlist *np;

    if ((*table_names).rows > BORDER)
        printf("FUNC %s -> В словаре более %d записей, сокращенная печать %d первых и %d последних\n", fname, BORDER, PRINT_NUM, PRINT_NUM);
    
    printf("\n\t============== Печать словаря =============\n");

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
                        printf("FUNC %s -> ошибка в поиске определения, слово № %d: %s", fname, i, np->name);
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
                        printf("FUNC %s -> ошибка в поиске определения, слово № %d: %s", fname, i, np->name);
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
                        printf("FUNC %s -> ошибка в поиске определения, слово № %d: %s", fname, i, np->name);
                }
        }
    
    printf("\n\t===========================================\n\n");
}


int compare_names_by_length_from_short(const void *name1, const void *name2)
/*
Функция сравнения по длине слова (от коротких к длинным)
*/
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;
                       
    return strlen((char*) *w1) - strlen((char*) *w2);
}


int compare_names_by_length_from_long(const void *name1, const void *name2)
/*
Функция сравнения по длине слова (от длинных к коротким)
*/
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;
                       
    return strlen((char*) *w2) - strlen((char*) *w1);
}


int compare_names_by_alph_from_a(const void *name1, const void *name2)
/*
Функция сравнения по алфавитному порядку (от А до Я)
*/
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;

    return strcmp((char*) *w1, (char*) *w2);
}


int compare_names_by_alph_from_z(const void *name1, const void *name2)
/*
Функция сравнения по алфавитному порядку (от Я до А)
*/
{
    char **w1, **w2;

    w1 = (char**) name1;
    w2 = (char**) name2;

    return strcmp((char*) *w2, (char*) *w1);
}


void sort_names(struct str_table *table_names, bool flag_alph, bool flag_order_from_min)
/*
Функция сортировки. Словарь сортируется по терминам. Можно отсортировать в алфавитном
(восходящем и нисходящем порядке), а также по длине термина (по возрастанию или по убыванию).
Если отсортировать термины, то это повлияет на порядок печати определений,
а также на порядок сохранения словарных записей в файл.
*/
{
    char *fname = "sort_names";

    
    if (flag_alph && flag_order_from_min) 
        {
            qsort((void*) (*table_names).records, (*table_names).rows, sizeof(char*), compare_names_by_alph_from_a);
            printf("FUNC %s -> термины отсортированы в алфавитном восходящем порядке\n", fname);
        }
    else if (flag_alph && (!flag_order_from_min)) 
        {
            qsort((void*) (*table_names).records, (*table_names).rows, sizeof(char*), compare_names_by_alph_from_z);
            printf("FUNC %s -> термины отсортированы в алфавитном нисходящем порядке\n", fname);
        }
    else if ((!flag_alph) && flag_order_from_min) 
        {
            qsort((void*) (*table_names).records, (*table_names).rows, sizeof(char*), compare_names_by_length_from_short);
            printf("FUNC %s -> термины отсортированы в порядке возрастания длины слова\n", fname);
        }
    else if ((!flag_alph) && (!flag_order_from_min))
        {
            qsort((void*) (*table_names).records, (*table_names).rows, sizeof(char*), compare_names_by_length_from_long);
            printf("FUNC %s -> термины отсортированы в порядке убвания длины слова\n", fname);
        }
}


int read_from_file(struct nlist **hashtable, struct str_table *table_names, char *file_path, bool print_flag)
/*
Функция считывает форматированные строки вида <термин>|<определение>\n.
При этом в теле определения могут встречать знаки '|', это не будет 
считаться нарушением формата, функиця продолжит чтение файла.
В случае ошибки формата на какой-либо строке, чтение преркащается,
считанные строки остаюся в памяти
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
    
    printf("FUNC %s -> открытие файла по адресу '%s'\n", fname, file_path);
    printf("FUNC %s -> в память будут записаны термины (не более 99 символов) и их определения (не более 999 символов)\n", fname);

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
            while (true)                            //цикл записи термина
            /*
            Из цикла записи термина может быть три выхода:
            1) при достижении разделительного символа | (это стандартный вариант, не требующий дополнительной обработки);
            2) при достижении конца файла;
            3) при достижении символа конца строки (предполагается, что строка без разделителя не соответствует заданному формату),
            4) при достижении предела длины термина (99 символов)
            */
                {
                    c = fgetc(file_pointer);
                    if (c == '|' || feof(file_pointer) || c == '\n') //прекращение чтения термина в случаях 1-3
                        {
                            i++;
                            break;
                        }
                    if (c == '\t')                                   //заменяем табуляцю на пробел
                        name[i] = ' ';
                    else
                        name[i] = c;
                    i++;
                    if (i==99)                                       //прекразение чтения термина в случае 4
                        break;
                }
            name[i] = '\0';
            if (c != '|')
            /*
            Если достигнут предел длины строки (случай 4), пропускаем лишние символы пока не дойдем до разделителя, либо конца строки, либо конца файла.
            В последних двух случаях считаем, что формат нарушен, прекращаем чтение файла, удаляем лишнюю память
            */
                while (c != '|')
                    {
                        c = fgetc(file_pointer);
                        if (feof(file_pointer) || c == '\n')
                            break;
                    }
            if (feof(file_pointer) || c == '\n')    //если достигнут конец файла или конец строки (случаи 2 и 3), то формат нарушен, прекращаем чтение файла, освобождаем лишнюю память
                {
                    free((void*) name);
                    free((void*) defn);
                    break;
                }
                    
            if (print_flag)
                printf("FUNC %s -> считан термин '%s'\n", fname, name);
            i = 0;
            while (true)                            //цикл записи определения
            /*
            Из цикла записи определения может быть три варианта выхода:
            1) достигнут символ конца строки (это стандартный вариант);
            2) достигнут конец файла (это также может быть стандартным вариантом, не требующим дополнительной обработки);
            3) достигнут лимит длины строки для определения
            */
                {
                    c = fgetc(file_pointer);
                    if (c == '\n' || feof(file_pointer)) //выход из цикла по условиям 1 или 2
                        {
                            i++;
                            break;
                        }
                    defn[i] = c;
                    if (c == '\t')                  //заменяем символ табуляции на пробел
                        defn[i] = ' ';
                    else
                        defn[i] = c;
                    i++;
                    if (i==999)                     //условие выхода из цикла записи определения при достижении предельной длины строки (строка 3)
                        break;
                }
            defn[i] = '\0';
            while (c != '\n' && !feof(file_pointer)) //выход из цикла записи определения состоялся в связи с превышением длины строки, пропускаем символы, пока не дойдем до конца строки или файла, если это последняя запись
                c = fgetc(file_pointer);
            
            if (print_flag)
                printf("FUNC %s -> считано определение '%s'\n", fname, defn);
            
            write_to_dict(hashtable, name, defn, write_to_dict_print_flag);             //запись в словарь термина и определения
            append_name_to_table(table_names, name, append_name_to_table_print_flag);   //запись термина в таблицу терминов
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
Функция записи словаря в текстовый файл. Формат строки записис: <термин>|<определение>\n.
Файл открывается в режиме 'a+', то есть содержание фамйла при записи будет сохранено.
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
    
    printf("FUNC %s -> открытие файла по адресу '%s'\n", fname, file_path);
    printf("FUNC %s -> в файл будут записаны термины и определения через разделительный символ '|'\n", fname);

    fseek(file_pointer, 0l, SEEK_SET); //Если файл не пустой, добавляем символ конца строки
    il_s = ftell(file_pointer);
    fseek(file_pointer, 0l, SEEK_END);
    il_e = ftell(file_pointer);
    if (il_s != il_e)
        {
            printf("FUNC %s -> в открытом файле уже есть запись, добавляем символ конца строки ('\\n')\n", fname);
            fputs("\n", file_pointer);
        }

    for (i=0; i<(*table_names).rows; i++)   //цикл записи строки заданого формата: <термин>|<определение>\n.
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