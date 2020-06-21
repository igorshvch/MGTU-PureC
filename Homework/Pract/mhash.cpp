/*
В данном файле реализован тип хэш-таблицы. Основа кода - пример из книги Кернигана и Ритчи (раздел 6.6., издание 2, в код внесенеы небольшие изменения),
а также решение задания к этому примеру (функция удаления записи из словаря erase_from_dict()).
*/
#include "mfuncs.h"


int mhash(char *str)
/*
Функция вычисляет хэш-значение поданной строки
*/
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
/*
Функция выдяляет память для записи строки в словарь
*/
{
    char *fname = "str_duplicate";
    char *copy_str;

    copy_str = (char*) malloc(strlen(str)+1);
    if (copy_str != NULL)
        {
            copy_str = strcpy(copy_str, str);
            if (print_flag)
                printf("FUNC %s -> строка '%s' успешно скопирована\n", fname, copy_str);
        }
    else
        printf("FUNC %s -> не удалось выделить память\n", fname);
    
    return copy_str;
}


nlist *lookup(struct nlist **hashtable, char *name, bool print_flag)
/*
Функция ищет термин в словаря. Для предотвращения коллизий, когда хэш-суммы строк совпадают, реализован связаный список
из структур с одинаковым значением хэша. Если в таблице записей словаря
есть запись с вычисленным хэшем, то тогда в переменную np передается указатель на первую структуру в связном списке.
Далее в цикле осуществляется проходка по связному списку из структур. У каждой стрктуры проверяется, соответствует ли
строка, на которую указывает поле name, поданной в функцию строке. Если да, функция возвращает соответствующу структуру.
*/
{
    char *fname = "lookup";
    int hashval;
    nlist *np;

    hashval = mhash(name);

    for(np = hashtable[hashval]; np != NULL; np = np->next)
        if (strcmp(name, np->name) == 0)
            {
                if (print_flag)
                    printf("FUNC %s -> термин '%s' уже в словаре\n", fname, name);
                return np;
            }
    
    return NULL;
}


nlist *write_to_dict(struct nlist **hashtable,  char *name, char *defn, bool print_flag)
/*
Функция запипи термина и определения в хэш-таблицу. Если термин уже есть, то обновляем определение
*/
{
    char *fname = "write_to_dict";
    nlist *np;
    unsigned hashval;
    const bool lookup_print_flag = print_flag;
    const bool str_duplicate_flag = print_flag;

    np = lookup(hashtable, name, lookup_print_flag); //проверяем наличие термина в словаре
    
    if (np == NULL) //термина нет в хэш-таблице
        {
            np = (nlist*) malloc(sizeof(*np));
            np->name = str_duplicate(name, str_duplicate_flag);
            if (np == NULL || np->name == NULL)
                {
                    printf("FUNC %s -> не удалось выделить память или скопировать строку с термином\n", fname);
                    return NULL;
                }
            hashval = mhash(name);
            np->next = hashtable[hashval];
            hashtable[hashval] = np;

            if (print_flag)
                printf("FUNC %s -> запись успешно добавлена\n", fname);
        }
    else //термин уже в словаре. Удаляем текущее определение
        if (print_flag)
            {
                printf("FUNC %s -> термин уже в словаре, обновляем определение\n", fname);
                free ((void*) np->defn);
            }
    
    np->defn = str_duplicate(defn, str_duplicate_flag);
    
    if (np->defn == NULL)
        {
            if (print_flag)
                printf("FUNC %s -> не удалось выделить пмять для определения, присвоено занчение NULL\n", fname);
            return NULL;
        }
    
    if (print_flag)
        {
            printf("FUNC %s -> в словарь внесена новая запись:\n", fname);
            print_nlist(fname, np);
        }

    return np;
}


void erase_from_dict(struct nlist **hashtable, char *name)
/*
Функция удаления записи из словаря
*/
{
    char *fname = "erase_from_dict";
    int hashval;
    nlist *np, *prev_np;

    prev_np = NULL;

    hashval = mhash(name);    
    
    for (np = hashtable[hashval]; np != NULL; np = np->next) //ищем запись с заданным термином, а также сохраняем предшествующую запись в переменную prev_np
        {
            if (strcmp(name, np->name) == 0)
                break;
            prev_np = np;
        }
    
    if (np != NULL) //если запись найдена, то удаляем ее, соединяя предыдущую запись с последующей
        {
            if (prev_np == NULL)    //если предшествующей записи нет (то есть коллизии не произошло и в списке только одна структура)
                hashtable[hashval] = prev_np;
            else                    //если была коллизия, в списке несколько структур, то соединяем предшествующую с последующей - обновляем поле next структуры prev_np
                prev_np->next = np->next;
            free((void*) np->name);
            free((void*) np->defn);
            free((void*) np);
            printf("FUNC %s -> запись с ключом '%s' удалена\n", fname, name);
        }
    else //если записи нет, выводим сообщение
        printf("FUNC %s -> запись с плючом '%s' в словаре отсутствует\n", fname, name);
}


void erase_defn(struct nlist **hashtable, char *name)
/*
Удаление определения для заданного термина. Сам термин остается неизменным.
*/
{
    char *fname = "erase_defn";
    int hashval;
    nlist *np;

    np = lookup(hashtable, name, false); //ищем запись с заданным термином

    if (np != NULL)
        {
            np->defn = NULL;
            printf("FUNC %s -> определение термина '%s' удалено\n", fname, name);
        }
    else
        printf("FUNC %s -> запись с плючом '%s' в словаре отсутствует\n", fname, name);
}


void find_record(struct nlist **hashtable, char *name)
/*
Проверка наличия записи в словаре по заданному термину
*/
{
    char *fname = "find_record";
    nlist *np;

    np = lookup(hashtable, name, false);

    if (np != NULL)
        {
            printf("FUNC %s -> запись с ключом '%s' найдена!\n", fname, name);
            print_nlist(fname, np);
        }
    else
        printf("FUNC %s -> запись с ключом '%s' НЕ найдена!\n", fname, name);
}


void erase_all_dict(struct nlist **hashtable, char **records, int rows)
/*
Удаление всего словаря. Используется двумерный массив, в котором содержатся все введенные термины. Операции над ним опредены в файле miohandler.cpp
*/
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
    printf("FUNC %s -> словарь удален из памяти\n", fname);
}


void print_nlist(char *fname, nlist *np)
/*
Печать всех полей поданной структуры
*/
{
    printf("FUNC %s -> nlist pose >> %p, np.next=%p, nlist.name=%s, nlist.defn=%s\n", fname, np, np->next, np->name, np->defn);
}