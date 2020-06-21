#include "mmenu.h"

static struct nlist *hashtable[HASHSIZE]; //структура объявлена в mhach.h
static struct str_table *table_names;     //стукрутар объявлена в miohandler.h


void user_input_reader(int *selection_holder, char **options, int options_num, char *menu_level)
/*
Универсальный считыватель ввода.
Предполагется, что опций в меню не более 10 (от 0 до 9).
*/
{
    char option = '0';
    char last_option_char = options_num-1 + '0';

    printf("\n%s%s%s\n", INDENT, INDENT, menu_level); //INDENT определен в файле mmenu.h
    printf("============================================================\n");

    while (true)
        {
            for (int i = 0; i<options_num; i++)
                printf("%s%d) %s\n", INDENT, i, options[i]);
            printf(">>> ");
            option = getch();
            if ((option >= '0') && (option <= last_option_char))
                break;
            else
                printf("\n%s%sВведено некорректное значение!\n\n", INDENT, INDENT);
        }
    *selection_holder = option - '0';
}


void menu_main()
/*
Меню верхнего уровня. Пользователю предлагается выбрать между
основными функциями программы. Далее, в зависимости от выбора,
пользователь попадет в соответствующее подменю либо программа
завершиться.
*/
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    
    table_names = (struct str_table*) malloc(sizeof(struct str_table));
    
    const int N = 3;
    char *options[N] = {"Выход", "Создать из консоли", "Открыть из файла"};
    int selection_holder = 0;

    user_input_reader(&selection_holder, options, N, "Главное меню");

    printf("%d\n", selection_holder);

    switch (selection_holder)
        {
            case 0:
                printf("Завершение программы\n");
                break;
            case 1:
                menu_create_from_console();
                break;
            case 2:
                menu_open();
                break;
        }
}


void menu_create_from_console()
/*
Меню создания словаря путем считывания консольного ввода и его записи в хэш-таблицу, а также
записи терминов в таблицу терминов.
*/
{
    int option = '6';

    char *name, *defn;

    printf("\n%sСоздание словаря посредством консольного ввода\n", INDENT);
    printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);

    while ((option - '0') != 0)
        {
            printf("%sВведите слово:\n>>> ", INDENT);
            name = read_str_from_console(hashtable, table_names, true, true);
            printf("%sВведите определение:\n>>> ", INDENT);
            defn = read_str_from_console(hashtable, table_names, false, false);
            write_to_dict(hashtable, name, defn);
            printf("%sПродолжить добавление записей в словарь (для прекращения нажмите 0)?\n>>> ", INDENT);
            option = getch();
            if ((option - '0') == 0)
                printf("%c\n", option);
            else
                printf("Продолжение формирования словаря\n");
        }
    menu_manage_dict();
}


void menu_open()
/*
Меню записи словаря в память из файла
*/
{
    char *fname = "menu_open";
    char *file_path;
    int i;
    signed int ret_val;
    bool print_flag = false;

    printf("%sВведите путь к текстовому файлу со словарем\n", INDENT);
    printf("%sДиректории могут разделяться как символом '/', так и символом '\\'\n", INDENT);
    printf("%sВводимые строки должны оканчиваться символом '|'\n>>> ", INDENT);
    file_path = read_str_from_console(hashtable, table_names, false, false, true);
    printf("%sВводить подробную информацию об обработке файла (0 - нет)?\n>>> ", INDENT);
    scanf("%d", &i);
    print_flag = (bool) i;
    print_flag ? printf(">>> Да\n", INDENT) : printf(">>> Нет\n", INDENT);
    ret_val = read_from_file(hashtable, table_names, file_path, print_flag);
    switch (ret_val) 
    {
        case 0:
            printf("%sЧтение файла завершено, словарь записан в память\n", INDENT);
            printf("%sВ словарь в памяти записано %d терминов\n", INDENT, (*table_names).rows);
            break;
        case -1:
            printf("FUNC %s -> не удалось открыть файл по адресу '%s'! Данные не прочитаны!\n", fname, file_path);
            break;
        case -2:
            printf("FUNC %s -> не удалось закрыть файл!\n", fname);
            break;
    }
    free ((void*) file_path);
    menu_manage_dict();
}

void menu_manage_dict()
/*
Меню управления словарем в памяти.
Пользователь может:
1) добавить запись (обновить определение);
2) удалить запись;
3) удалить определение;
4) проверить наличие термина в словаре;
5) напечатать словарь в консоль (если словарь содержит более 20 записей, печать будет сокращена, см. функции печати в файле miohandler.cpp);
6) отсортировать термины;
7) сохранить словарь в файл;
8) удалить словарь из памяти
*/
{
    bool save_flag = false;
    int save_option = 1;

    const int N = 9;
    char *options[N] = {
        "Выход",
        "Добавит новую запись (обновить существующее определение)",
        "Удалить запись",
        "Удалить определение",
        "Проверить наличие термина в словаре",
        "Печать в консоль",
        "Сортировка",
        "Сохранить в файл",
        "Удалить словарь"
        };
    int selection_holder = 1;

    char *name, *defn;

    while (selection_holder != 0)
        {
            user_input_reader(&selection_holder, options, N, "Меню управления словарем");
            printf("%d\n", selection_holder);
            switch (selection_holder)
                {
                    case 0: //выход
                        if (!save_flag)
                            {
                                printf("%sСловарь не сохранен, сохранить (0 - нет)?\n>>> ", INDENT);
                                save_option = getch();
                                printf("%c\n", ((char) save_option));
                                if ((save_option - '0') != 0)
                                    {
                                        save_flag = 1;
                                        menu_save_to_file();
                                        printf("%sСловарь сохранен\n", INDENT);
                                    }
                                else
                                    printf("%sСловарь не сохранен\n", INDENT);
                            }
                        erase_all_dict(hashtable, table_names->records, table_names->rows);
                        delete_table(table_names);
                        printf("%sЗакрытие меню управления словарем, завершение программы\n", INDENT);
                        break;
                    case 1: //добавление записи или обновление определения
                        printf("\n%sДобавление новой записи\n", INDENT);
                        printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);
                        printf("%sВведите слово:\n>>> ", INDENT);
                        name = read_str_from_console(hashtable, table_names, true, true);
                        printf("%sВведите определение:\n>>> ", INDENT);
                        defn = read_str_from_console(hashtable, table_names, false, false);
                        write_to_dict(hashtable, name, defn);
                        save_flag = false;
                        break;
                    case 2: //удаление записи
                        printf("\n%sУдаление существующей записи\n", INDENT);
                        printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);
                        printf("%sВведите слово:\n>>> ", INDENT);
                        name = read_str_from_console(hashtable, table_names, true, false);
                        erase_from_dict(hashtable, name);
                        delete_name_from_table(table_names, name);
                        free((void*) name); //имя не заносится в таблицу терминов, освобождаем память, выделенную под строку ввода
                        save_flag = false;
                        break;
                    case 3: //удаление определения
                        printf("\n%sУдаление определения\n", INDENT);
                        printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);
                        printf("%sВведите слово:\n>>> ", INDENT);
                        name = read_str_from_console(hashtable, table_names, true, false);
                        erase_defn(hashtable, name);
                        free((void*) name); //имя не заносится в таблицу терминов, освобождаем память, выделенную под строку ввода
                        save_flag = false;
                        break;
                    case 4: //проверка наличия записи в словаре
                        printf("\n%sПроверка наличия записи в словаре\n", INDENT);
                        printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);
                        printf("%sВведите слово:\n>>> ", INDENT);
                        name = read_str_from_console(hashtable, table_names, true, false);
                        find_record(hashtable, name);
                        free((void*) name); //имя не заносится в таблицу терминов, освобождаем память, выделенную под строку ввода
                        break;
                    case 5: //печать в консоль
                        menu_console_print();
                        break;
                    case 6: //сортировка
                        menu_sort();
                        save_flag = false;
                        break;
                    case 7: //сохранить в файл
                        menu_save_to_file();
                        save_flag = true;
                        break;
                    case 8: //удалить словарь
                        erase_all_dict(hashtable, table_names->records, table_names->rows);
                        delete_table(table_names);
                        printf("%sЗакрытие меню управления словарем, завершение программы\n", INDENT);
                        selection_holder = 0;
                        break;
                }
        }
}


void menu_console_print()
/*
Меню печати в консоль.
Можно распечатать только термины, только определения, либо все словарные статьи (печать будет сокращенной, если в словаре более 20 записей, см. miohandler.cpp)
*/
{
    const int N = 4;
    char *options[N] = {
        "Выход",
        "Печать терминов",
        "Печать определений",
        "Печать терминов и определений"
        };
    int selection_holder = 1;

    while (selection_holder != 0)
        {
            user_input_reader(&selection_holder, options, N, "Меню печати в консоль");
            printf("%d\n", selection_holder);
            switch(selection_holder)
                {
                    case 0:
                        printf("%sЗакрытие меню печати в консоль\n", INDENT);
                        break;
                    case 1:
                        print_names(table_names);
                        break;
                    case 2:
                        print_defns(hashtable, table_names);
                        break;
                    case 3:
                        print_all_dict_to_console(hashtable, table_names);
                        break;
                }
        }
}


void menu_sort()
/*
Меню сортировки.
Пользователь может отсортировать таблицу терминов по алфавиту, либо по длине слова.
В обоих случаях можно выбирать прямой или обратный порядок. Сортировка терминов повлияет
на печать в консоль и порядок сохранения словарных записей.
*/
{
    const int N = 5;
    char *options[N] = {
        "Выход",
        "Сортировать термины в алфавитном восходящем порядке",
        "Сортировать термины в алфавитном нисходящем порядке",
        "Сортировать термины в порядке возрастания длины слова",
        "Сортировать термины в порядке убывания длины слова"
        };
    int selection_holder = 0;

    user_input_reader(&selection_holder, options, N, "Меню сортировки");
    printf("%d\n", selection_holder);
    switch(selection_holder)
        {
            case 0:
                printf("%sЗакрытие меню сортировка\n", INDENT);
                break;
            case 1:
                sort_names(table_names, true, true);
                print_names(table_names);
                break;
            case 2:
                sort_names(table_names, true, false);
                print_names(table_names);
                break;
            case 3:
                sort_names(table_names, false, true);
                print_names(table_names);
                break;
            case 4:
                sort_names(table_names, false, false);
                print_names(table_names);
                break;
        }
}


void menu_save_to_file()
/*
Меню сохранения словаря в файл
*/
{
    char *fname = "menu_save_to_file";
    char *file_path;
    int ret_val;
    bool print_flag = false;

    printf("%sВведите путь к текстовому файлу, в котором будет сохранен словарь (если файла нет, он будет создан; содержимое существующего файла будет сохранено, новые данные будут записаны в конце файла)\n", INDENT);
    printf("%sДиректории могут разделяться как символом '/', так и символом '\\'\n", INDENT);
    printf("%sВводимые строки должны оканчиваться символом '|'\n>>> ", INDENT);
    file_path = read_str_from_console(hashtable, table_names, false, false, true);
    ret_val = save_to_file(hashtable, table_names, file_path);
    switch (ret_val) 
    {
        case 0:
            printf("%sЗапись файла завершена, словарь записан на диск\n", INDENT);
            printf("%sВ файл записано %d словарных записи(-ей)\n", INDENT, (*table_names).rows);
            break;
        case -1:
            printf("FUNC %s -> не удалось открыть файл по адресу '%s'! Данные не записаны на диск!\n", file_path, fname);
            break;
        case -2:
            printf("FUNC %s -> не удалось закрыть файл! Данные не записаны на диск!\n", fname);
            break;
    }
    free((void*) file_path);
}