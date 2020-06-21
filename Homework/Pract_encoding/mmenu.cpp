#include "mmenu.h"

static nlist *hashtable[HASHSIZE];


void user_input_reader(int *selection_holder, char **options, int options_num, char *menu_level)
/*
������������� ����������� �����.
�������������, ��� ����� � ���� �� ����� 10 (�� 0 �� 9).
*/
{
    char option = '0';
    char last_option_char = options_num-1 + '0';

    printf("\n%s%s%s\n", INDENT, INDENT, menu_level);
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
                printf("\n%s%s������� ������������ ��������!\n\n", INDENT, INDENT);
        }
    *selection_holder = option - '0';
}


void menu_main()
/*
���� �������� ������. ������������ ������������ ������� �����
��������� ��������� ���������. �����, � ����������� �� ������,
������������ ������� � ��������������� ������� ���� ���������
�����������.
*/
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);
    
    const int N = 3;
    char *options[N] = {"�����", "������� �� �������", "������� �� �����"};
    int selection_holder = 0;

    user_input_reader(&selection_holder, options, N, "������� ����");

    printf("%d\n", selection_holder);

    switch (selection_holder)
        {
            case 0:
                printf("���������� ���������\n");
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
{
    int option = '6';

    char *name, *defn;

    printf("\n%s�������� ������� ����������� ����������� �����\n", INDENT);
    printf("%s�������� ������ ������ ������������ �������� '|'\n", INDENT);

    while ((option - '0') != 0)
        {
            printf("%s������� �����:\n>>> ", INDENT);
            name = read_str_from_console(hashtable, true, true);
            printf("%s������� �����������:\n>>> ", INDENT);
            defn = read_str_from_console(hashtable, false, false);
            write_to_dict(name, defn);
            printf("%s���������� ���������� ������� � ������� (��� ����������� ������� 0)?\n>>> ", INDENT);
            option = getch();
            if ((option - '0') == 0)
                printf("%c\n", option);
            else
                printf("����������� ������������ �������\n");
        }
    menu_manage_dict();
}


void menu_open()
{
    char *file_path;

    printf("%s������� ���� � ���������� ����� �� ��������\n", INDENT);
    printf("%s���������� ����� ����������� ��� �������� '/', ��� � �������� '\\'\n", INDENT);
    printf("%s�������� ������ ������ ������������ �������� '|'\n>>> ", INDENT);
    file_path = read_str_from_console(false, false, true);
    read_from_file(file_path);
    menu_manage_dict();
}

void menu_manage_dict()
{
    bool save_flag = false;
    int save_option = 1;

    const int N = 9;
    char *options[N] = {
        "�����",
        "������� ����� ������ (�������� ������������ �����������)",
        "������� ������",
        "������� �����������",
        "��������� ������� ������� � �������",
        "������ � �������",
        "����������",
        "��������� � ����",
        "������� �������"
        };
    int selection_holder = 1;

    char *name, *defn;

    while (selection_holder != 0)
        {
            user_input_reader(&selection_holder, options, N, "���� ���������� ��������");
            printf("%d\n", selection_holder);
            switch (selection_holder)
                {
                    case 0: //�����
                        if (!save_flag)
                            {
                                printf("%s������� �� ��������, ��������� (0 - ���)?\n>>> ", INDENT);
                                save_option = getch();
                                printf("%c\n", ((char) save_option));
                                if ((save_option - '0') != 0)
                                    {
                                        save_flag = 1;
                                        ; // ����� ������ ���� ������� ���������� � ����
                                        printf("%s������� ��������\n", INDENT);
                                    }
                                else
                                    printf("%s������� �� ��������\n", INDENT);
                                    
                            }
                        printf("%s�������� ���� ���������� ��������, ���������� ���������\n", INDENT);
                        break;
                    case 1: //���������� ������ ��� ���������� �����������
                        printf("\n%s���������� ����� ������\n", INDENT);
                        printf("%s�������� ������ ������ ������������ �������� '|'\n", INDENT);
                        printf("%s������� �����:\n>>> ", INDENT);
                        name = read_str_from_console(true, true);
                        printf("%s������� �����������:\n>>> ", INDENT);
                        defn = read_str_from_console(false, false);
                        write_to_dict(name, defn);
                        break;
                    case 2: //�������� ������
                        printf("\n%s�������� ������������ ������\n", INDENT);
                        printf("%s�������� ������ ������ ������������ �������� '|'\n", INDENT);
                        printf("%s������� �����:\n>>> ", INDENT);
                        name = read_str_from_console(true, false);
                        erase_from_dict(name);
                        delete_name_from_table(name);
                        break;
                    case 3: //�������� �����������
                        printf("\n%s�������� �����������\n", INDENT);
                        printf("%s�������� ������ ������ ������������ �������� '|'\n", INDENT);
                        printf("%s������� �����:\n>>> ", INDENT);
                        name = read_str_from_console(true, false);
                        erase_defn(name);
                        break;
                    case 4: //�������� ������� ������ � �������
                        printf("\n%s�������� ������� ������ � �������\n", INDENT);
                        printf("%s�������� ������ ������ ������������ �������� '|'\n", INDENT);
                        printf("%s������� �����:\n>>> ", INDENT);
                        name = read_str_from_console(true, false);
                        find_record(name);
                        break;
                    case 5: //������ � �������
                        menu_console_print();
                        break;
                    case 6: //����������
                        menu_sort();
                        break;
                    case 7: //��������� � ����
                        save_flag = true;
                        break; //��������!
                    case 8: //������� �������
                        extern str_table table_names;
                        erase_all_dict(table_names.records, table_names.rows);
                        delete_table();
                        printf("%s�������� ���� ���������� ��������, ���������� ���������\n", INDENT);
                        selection_holder = 0;
                        break;
                }
        }
}


void menu_console_print()
{
    const int N = 4;
    char *options[N] = {
        "�����",
        "������ ��������",
        "������ �����������",
        "������ �������� � �����������"
        };
    int selection_holder = 1;

    while (selection_holder != 0)
        {
            user_input_reader(&selection_holder, options, N, "���� ������ � �������");
            printf("%d\n", selection_holder);
            switch(selection_holder)
                {
                    case 0:
                        printf("%s�������� ���� ������ � �������\n", INDENT);
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


void menu_sort()
{
    const int N = 5;
    char *options[N] = {
        "�����",
        "����������� ������� � ���������� ���������� �������",
        "����������� ������� � ���������� ���������� �������",
        "����������� ������� � ������� ����������� ����� �����",
        "����������� ������� � ������� �������� ����� �����"
        };
    int selection_holder = 0;

    user_input_reader(&selection_holder, options, N, "���� ����������");
    printf("%d\n", selection_holder);
    switch(selection_holder)
        {
            case 0:
                printf("%s�������� ���� ����������\n", INDENT);
                break;
            case 1:
                sort_names(true, true);
                print_names();
                break;
            case 2:
                sort_names(true, false);
                print_names();
                break;
            case 3:
                sort_names(false, true);
                print_names();
                break;
            case 4:
                sort_names(false, false);
                print_names();
                break;
        }
}