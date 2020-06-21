#include "mhash.h"


int mhash(char *str)
{
    char *fname = "hash";
    unsigned int hashval;

    for (hashval=0; *str != '\0'; str++)
        {
            hashval = *str + 31*hashval;
        }
    
    return hashval % HASHSIZE;
}


char *str_duplicate(char *str, bool print_flag)
{
    char *fname = "str_duplicate";
    char *copy_str;

    copy_str = (char*) malloc(strlen(str)+1);
    if (copy_str != NULL)
        {
            copy_str = strcpy(copy_str, str);
            if (print_flag)
                printf("FUNC %s -> ������ '%s' ������� �����������\n", fname, copy_str);
        }
    else
        printf("FUNC %s -> �� ������� �������� ������\n", fname);
    
    return copy_str;
}


nlist *lookup(struct nlist **hashtable, char *name, bool print_flag)
{
    char *fname = "lookup";
    int hashval;
    nlist *np;

    hashval = mhash(name);

    for(np = hashtable[hashval]; np != NULL; np = np->next)
        if (strcmp(name, np->name) == 0)
            {
                if (print_flag)
                    printf("FUNC %s -> ���� '%s' ��� � �������\n", fname, name);
                return np;
            }
    
    return NULL;
}


nlist *write_to_dict(struct nlist **hashtable,  char *name, char *defn, bool print_flag)
{
    char *fname = "write_to_dict";
    nlist *np;
    unsigned hashval;
    const bool lookup_print_flag = print_flag;
    const bool str_duplicate_flag = print_flag;

    np = lookup(hashtable, name, lookup_print_flag);
    
    if (np == NULL)
        {
            np = (nlist*) malloc(sizeof(*np));
            np->name = str_duplicate(name, str_duplicate_flag);
            if (np == NULL || np->name == NULL)
                {
                    printf("FUNC %s -> �� ������� �������� ������ ��� ����� ������\n", fname);
                    return NULL;
                }
            hashval = mhash(name);
            np->next = hashtable[hashval];
            hashtable[hashval] = np;

            if (print_flag)
                printf("FUNC %s -> ������� ����� ������\n", fname);
        }
    else
        if (print_flag)
            {
                printf("FUNC %s -> ������ ��� � �������, ��������� �����������\n", fname);
                free ((void*) np->defn);
            }
    
    np->defn = str_duplicate(defn, str_duplicate_flag);
    
    if (np->defn == NULL)
        {
            if (print_flag)
                printf("FUNC %s -> �� ������� �������� ������ ��� �����������, ���������� NULL\n", fname);
            return NULL;
        }
    
    if (print_flag)
        {
            printf("FUNC %s -> ����� ������ � �������:\n", fname);
            print_nlist(fname, np);
        }

    return np;
}


void erase_from_dict(struct nlist **hashtable, char *name)
{
    char *fname = "erase_from_dict";
    int hashval;
    nlist *np, *prev_np;

    prev_np = NULL;

    hashval = mhash(name);    
    
    for (np = hashtable[hashval]; np != NULL; np = np->next)
        {
            if (strcmp(name, np->name) == 0)
                break;
            prev_np = np;
        }
    
    if (np != NULL)
        {
            if (prev_np == NULL)
                hashtable[hashval] = prev_np;
            else
                prev_np->next = np->next;
            free((void*) np->name);
            free((void*) np->defn);
            free((void*) np);
            printf("FUNC %s -> ������ c ������ '%s' �������\n", fname, name);
        }
    else
        printf("FUNC %s -> ������ c ������ '%s' � ������� �����������\n", fname, name);
}


void erase_defn(struct nlist **hashtable, char *name)
{
    char *fname = "erase_defn";
    int hashval;
    nlist *np;

    np = lookup(hashtable, name, false);

    if (np != NULL)
        {
            np->defn = "";
            printf("FUNC %s -> ����������� ������� '%s' �������\n", fname, name);
        }
    else
        printf("FUNC %s -> ������ � ������ '%s' � ������� �����������\n", fname, name);
}


void find_record(struct nlist **hashtable, char *name)
{
    char *fname = "find_record";
    nlist *np;

    np = lookup(hashtable, name, false);

    if (np != NULL)
        {
            printf("FUNC %s -> ������ '%s' �������!\n", fname, name);
            print_nlist(fname, np);
        }
    else
        printf("FUNC %s -> ������ �� '%s' �������!\n", fname, name);
}


void erase_all_dict(struct nlist **hashtable, char **records, int rows)
{
    char *fname = "erase_all_dict";
    const bool lookup_print_flag = false;

    int i;
    nlist *np;

    for(i=0; i<rows; i++)
        {
            np = lookup(hashtable, records[i], lookup_print_flag);
            free((void*) np->name);
            free((void*) np->defn);
            free((void*) np);
        }
    printf("FUNC %s -> ������� ������\n", fname);
}


void print_nlist(char *fname, nlist *np)
{
    printf("FUNC %s -> nlist pose >> %p, np.next=%p, nlist.name=%s, nlist.defn=%s\n", fname, np, np->next, np->name, np->defn);
}