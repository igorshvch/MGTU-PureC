#include "mhash.h"

#define INDENT "\t"


struct str_table  //структура для хранения таблицв терминов
{
    char **records;
    int rows;
};

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