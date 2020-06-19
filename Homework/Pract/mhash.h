#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define HASHSIZE 1653789

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};


static nlist *hashtable[HASHSIZE];

int mhash(char *str);
char *str_duplicate(char *str);
nlist *lookup(char *name, bool print_flag=true);
nlist *write_to_dict(char *name, char *defn);
void erase_from_dict(char *name);
void erase_defn(char *name);
void find_record(char *name);
void erase_all_dict(char **records, int rows);
void print_nlist(char *name, nlist *np);


