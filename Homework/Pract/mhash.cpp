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


char *str_duplicate(char *str)
{
    char *fname = "str_duplicate";
    char *copy_str;

    copy_str = (char*) malloc(strlen(str)+1);
    if (copy_str != NULL)
        {
            copy_str = strcpy(copy_str, str);
            printf("FUNC %s -> строка '%s' успещно скопирована\n", fname, copy_str);
        }
    else
        printf("FUNC %s -> не удалось выделить память\n", fname);
    
    return copy_str;
}


nlist *lookup(char *name, bool print_flag)
{
    char *fname = "lookup";
    int hashval;
    nlist *np;

    hashval = mhash(name);

    for(np = hashtable[hashval]; np != NULL; np = np->next)
        if (strcmp(name, np->name) == 0)
            {
                if (print_flag)
                    printf("FUNC %s -> ключ '%s' уже в словаре\n", fname, name);
                return np;
            }
    
    return NULL;
}


nlist *write_to_dict(char *name, char *defn)
{
    char *fname = "write_to_dict";
    nlist *np;
    unsigned hashval;

    np = lookup(name);
    
    if (np == NULL)
        {
            np = (nlist*) malloc(sizeof(*np));
            np->name = str_duplicate(name);
            if (np == NULL || np->name == NULL)
                {
                    printf("FUNC %s -> не удалось выделить память для новой записи\n", fname);
                    return NULL;
                }
            hashval = mhash(name);
            np->next = hashtable[hashval];
            hashtable[hashval] = np;

            printf("FUNC %s -> создана новая запись\n", fname);
        }
    else
        printf("FUNC %s -> запись уже в словаре, обновляем определение\n", fname);
        free ((void*) np->defn);
    
    np->defn = str_duplicate(defn);
    
    if (np->defn == NULL)
        {
            printf("FUNC %s -> не удалось выделить память для определения, возвращаем NULL\n", fname);
            return NULL;
        }
    
    printf("FUNC %s -> новая запись в словаре:\n", fname);
    print_nlist(fname, np);

    return np;
}


void erase_from_dict(char *name)
{
    char *fname = "erase_from_dict";
    int hashval;
    nlist *np, *prev_np;

    prev_np = NULL;

    np = lookup(name, false);

    if (np != NULL)
        {
            hashval = mhash(name);    
            
            for (np = hashtable[hashval]; np != NULL; np = np->next)
                if (strcmp(name, np->name) == 0)
                    break;
                prev_np = np;
            
            if (np != NULL)
                if (prev_np == NULL)
                    hashtable[hashval] = prev_np;
                else
                    {
                        prev_np->next = np->next;
                    }
                free((void*) np->name);
                free((void*) np->defn);
                free((void*) np);
                printf("FUNC %s -> запись c ключом '%s' удалена\n", fname, name);
        }
    else
        printf("FUNC %s -> запись c ключом '%s' в словаре отсутствует\n", fname, name);
}


void erase_defn(char *name)
{
    char *fname = "erase_defn";
    int hashval;
    nlist *np;

    np = lookup(name, false);

    if (np != NULL)
        {
            np->defn = "";
            printf("FUNC %s -> определение термина '%s' удалено\n", fname, name);
        }
    else
        printf("FUNC %s -> запись с ключом '%s' в словаре отсутствует\n", fname, name);
}


void find_record(char *name)
{
    char *fname = "find_record";
    nlist *np;

    np = lookup(name, false);

    if (np != NULL)
        {
            printf("FUNC %s -> запись '%s' найдена!\n", fname, name);
            print_nlist(fname, np);
        }
    else
        printf("FUNC %s -> запись НЕ '%s' найдена!\n", fname, name);
}


void erase_all_dict(char **records, int rows)
{
    char *fname = "erase_all_dict";

    int i;
    nlist *np;

    for(i=0; i<rows; i++)
        {
            np = lookup(records[i], false);
            free((void*) np->name);
            free((void*) np->defn);
            free((void*) np);
        }
    printf("FUNC %s -> словарь удален\n", fname);
}


void print_nlist(char *fname, nlist *np)
{
    printf("FUNC %s -> nlist pose >> %p, np.next=%p, nlist.name=%s, nlist.defn=%s\n", fname, np, np->next, np->name, np->defn);
}