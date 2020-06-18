#include "mhash.h"

#define INDENT "\t"


struct str_table
{
    char **records;
    int rows = 0;
};

static str_table table_names;


char *read_name_from_console();
char *read_defn_from_console();
str_table append_str_to_table(str_table table, char *str);
void print_names();
void print_defns();
void print_all_dict_to_console();