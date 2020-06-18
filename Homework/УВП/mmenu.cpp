#include "mmenu.h"


void user_input_reader(int *selection_holder, char **options, int options_num, char *menu_level)
/*
Универсальный считыватель ввода.
Предполагется, что опций в меню не более 10 (от 0 до 9).
*/
{
    char *fname = "user_input_reader";

    char option = '0';
    char last_option_char = options_num-1 + '0';

    printf("\n%s%s%s\n", INDENT, INDENT, menu_level);
    printf("============================================================\n");

    while (true)
        {
            for (int i = 0; i<options_num; i++)
                printf("%s%d) %s\n", INDENT, i, options[i]);
            option = getch();
            if ((option >= '0') && (option <= last_option_char))
                break;
            else
                printf("%s%sВведено некорректное значение!\n\n", INDENT, INDENT);
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

    char *fname = "menu_main";
    
    const int N = 3;
    char *options[N] = {"Выход", "Создать", "Открыть"};
    int selection_holder = 0;

    user_input_reader(&selection_holder, options, N, "Главное меню");

    printf(">>> %d\n", selection_holder);

    switch (selection_holder)
        {
            case 0:
                printf("Завершение программы\n");
                break;
            case 1:
                menu_creation();
                break;
            case 2:
                menu_open();
                break;
        }
}


void menu_creation()
{
    char *fname = "menu_creation";

    const int N = 3;
    char *options[N] = {"Выход", "Создать из консоли", "Создать из файла"};
    int selection_holder = 0;

    user_input_reader(&selection_holder, options, N, "Меню создания словаря");

    printf(">>> %d\n", selection_holder);

    switch (selection_holder)
        {
            case 0:
                printf("%sЗакрытие меню создания, завершение программы\n", INDENT);
                break;
            case 1:
                menu_create_from_console();
                break;
            case 2:
                ; // здесь должны быть функция, обрабатывающая ввод, связанный с созданием файла
                break;
        }
}

void menu_create_from_console()
{
    char *fname = "menu_create_from_console";

    int option = '6';

    char *name, *defn;

    printf("\n%sСоздание словаря посредством консольного ввода\n", INDENT);
    printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);

    while ((option - '0') != 0)
        {
            printf("%sВведите слово:\n", INDENT);
            name = read_name_from_console();
            printf("%sВведите определение:\n", INDENT);
            defn = read_defn_from_console();
            write_to_dict(name, defn);
            printf("%sПродолжить добавление записей в словарь (для прекращения нажмите 0)?\n", INDENT);
            option = getch();
            printf(">>> %c\n", option);
        }
    
    menu_manage_dict();
}


void menu_open()
{
    char *fname = "menu_open";

    const int N = 2;
    char *options[N] = {"Выход", "Открыть"};
    int selection_holder = 0;

    user_input_reader(&selection_holder, options, N, "Меню чтения словаря из файла");

    printf("FUNC %s -> Значение пользовательского ввода равно %d\n", fname, selection_holder);

    switch (selection_holder)
        {
            case 0:
                printf("%sЗакрытие меню чтения, завершение программы\n", INDENT);
                break;
            case 1:
                ; // здесь додлжна быть функция обработки ввода, связанного с адресом открытия
                menu_manage_dict();
                break;
        }
}

void menu_manage_dict()
{
    char *fname = "menu_manage_dict";

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
            printf(">>> %d\n", selection_holder);
            switch (selection_holder)
                {
                    case 0: //выход
                        if (!save_flag)
                            {
                                printf("%sСловарь не сохранен, сохранить (0 - нет)?\n", INDENT);
                                save_option = getch();
                                printf(">>> %c\n", ((char) save_option));
                                if ((save_option - '0') != 0)
                                    {
                                        save_flag = 1;
                                        ; // Здесь должны быть функция сохранения в файл
                                        printf("%sСловарь сохранен\n", INDENT);
                                    }
                                else
                                    printf("%sСловарь не сохранен\n", INDENT);
                                    
                            }
                        printf("%sЗакрытие меню управления словарем, завершение программы\n", INDENT);
                        break;
                    case 1: //добавление записи или обновление определения
                        printf("\n%sДобавление новой записи\n", INDENT);
                        printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);
                        printf("%sВведите слово:\n", INDENT);
                        name = read_name_from_console();
                        printf("%sВведите определение:\n", INDENT);
                        defn = read_defn_from_console();
                        write_to_dict(name, defn);
                        break;
                    case 2: //удаление записи
                        printf("\n%sУдаление существующей записи\n", INDENT);
                        printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);
                        printf("%sВведите слово:\n", INDENT);
                        name = read_name_from_console();
                        erase_from_dict(name);
                        break;
                    case 3: //удаление определения
                        printf("\n%sУдаление определения\n", INDENT);
                        printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);
                        printf("%sВведите слово:\n", INDENT);
                        name = read_name_from_console();
                        write_to_dict(name, "");
                        break;
                    case 4: //проверка наличия записи в словаре
                        printf("\n%sПроверка наличия записи в словаре\n", INDENT);
                        printf("%sВводимые строки должны оканчиваться символом '|'\n", INDENT);
                        printf("%sВведите слово:\n", INDENT);
                        name = read_name_from_console();
                        find_record(name);
                        break;
                    case 5: //печать в консоль
                        menu_console_print();
                        break;
                    case 6: //сортировка
                        break;
                    case 7: //сохранить в файл
                        save_flag = true;
                        break;
                    case 8: //удалить словарь
                        save_flag = true;
                        break;
                }
        }
}


void menu_console_print()
{
    char *fname = "menu_console_print";

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
            printf(">>> %d\n", selection_holder);
            switch(selection_holder)
                {
                    case 0:
                        printf("%sЗакрытие меню печати в консоль\n", INDENT);
                        break;
                    case 1:
                        print_names();
                        break;
                    case 2:
                        print_defns();
                        break;
                    case 3:
                        print_all_dict_to_console();
                        break;
                }
        }
}

