#include "mhash.h"

#define INDENT "\t"


struct str_table
{
    char **records;
    int rows = 0;
};

static str_table table_names;

char *read_str_from_console(nlist **hashtable, bool name_mode_flag, bool save_name_flag, bool format_path_flag);
void append_name_to_table(char *str);
void delete_name_from_table(char *str);
void delete_table();
void print_names();
void print_defns(nlist **hashtable);
void print_all_dict_to_console(nlist **hashtable);
int compare_names_by_length_from_short(const void *name1, const void *name2);
int compare_names_by_length_from_long(const void *name1, const void *name2);
int compare_names_by_alph_from_a(const void *name1, const void *name2);
int compare_names_by_alph_from_z(const void *name1, const void *name2);
void sort_names(bool flag_alph, bool flag_order_from_min);

int read_from_file(nlist **hashtable, char *file_path);