#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define HASHSIZE 1653789

struct nlist        //структура для хранения связного списка (используется для предотвращения коллизий хэш-функции)
{
    struct nlist *next;
    char *name;
    char *defn;
};

int mhash(char *str);
char *str_duplicate(char *str, bool print_flag=true);
nlist *lookup(nlist **hashtable, char *name, bool print_flag=true);
nlist *write_to_dict(nlist **hashtable, char *name, char *defn, bool print_flag=true);
void erase_from_dict(nlist **hashtable, char *name);
void erase_defn(nlist **hashtable, char *name);
void find_record(struct nlist **hashtable, char *name);
void erase_all_dict(nlist **hashtable, char **records, int rows);
void print_nlist(char *name, nlist *np);


