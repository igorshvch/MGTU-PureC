#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
nlist *lookup(char *name);
nlist *write_to_dict(char *name, char *defn);
void erase_from_dict(char *name);
void find_record(char *name);
void print_nlist(char *name, nlist *np);


