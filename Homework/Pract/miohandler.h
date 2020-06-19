#include "mhash.h"

#define INDENT "\t"


struct str_table
{
    char **records;
    int rows = 0;
};

static str_table table_names;


char *read_name_from_console(bool save_name_flag=true);
char *read_defn_from_console();
void append_name_to_table(char *str);
void delete_name_from_table(char *str);
void delete_table();
void print_names();
void print_defns();
void print_all_dict_to_console();
int compare_names_by_length(const void *name1, const void *name2);