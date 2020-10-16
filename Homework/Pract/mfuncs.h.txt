#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>

#define INDENT "\t"
#define HASHSIZE 1653789

struct nlist        //структура для хранения связного списка (используется для предотвращения коллизий хэш-функции)
{
    struct nlist *next;
    char *name;
    char *defn;
};

struct str_table  //структура для хранения таблицв терминов
{
    char **records;
    int rows;
};


//mhash.cpp
int mhash(char *str);
char *str_duplicate(char *str, bool print_flag=true);
nlist *lookup(nlist **hashtable, char *name, bool print_flag=true);
nlist *write_to_dict(nlist **hashtable, char *name, char *defn, bool print_flag=true);
void erase_from_dict(nlist **hashtable, char *name);
void erase_defn(nlist **hashtable, char *name);
void find_record(struct nlist **hashtable, char *name);
void erase_all_dict(nlist **hashtable, char **records, int rows);
void print_nlist(char *name, nlist *np);


//miohandler.cpp
char *read_str_from_console(struct nlist **hashtable, struct str_table *table_names, bool name_mode_flag, bool save_name_flag, bool format_path_flag=false);

void append_name_to_table(struct str_table *table_names, char *str, bool print_flag=true);
void delete_name_from_table(struct str_table *table_names, char *str);
void delete_table(struct str_table *table_names);

void print_names(struct str_table *table_names);
void print_defns(struct nlist **hashtable, struct str_table *table_names);
void print_all_dict_to_console(struct nlist **hashtable, struct str_table *table_names);

int compare_names_by_length_from_short(const void *name1, const void *name2);
int compare_names_by_length_from_long(const void *name1, const void *name2);
int compare_names_by_alph_from_a(const void *name1, const void *name2);
int compare_names_by_alph_from_z(const void *name1, const void *name2);
void sort_names(struct str_table *table_names, bool flag_alph, bool flag_order_from_min);

int read_from_file(struct nlist **hashtable, struct str_table *table_names, char *file_path, bool print_flag=false);
int save_to_file(struct nlist **hashtable, struct str_table *table_names, char *file_path);


//mmenu.cpp
void user_input_reader(int *selection_holder, char **options, int options_num, char *menu_level);
void menu_main();
void menu_create_from_console();
void menu_open();
void menu_manage_dict();
void menu_console_print();
void menu_sort();
void menu_save_to_file();