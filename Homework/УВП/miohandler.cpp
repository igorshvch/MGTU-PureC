#include "miohandler.h"

char *read_name_from_console()
{
    char *fname = "read_name_from_console";

    char c;
    const int MAX_LEN = 100;
    int i = 0;
    char *name;
    char *name_trunkate;

    name = (char*) malloc(sizeof(char)*MAX_LEN);

    c = getchar();
    if (c == '\n' || c == ' ')
        c = getchar();
    
    while (c != '|')
        {
            name[i] = c;
            i++;
            if (i == (MAX_LEN-1))
                {
                    printf("\nFUNC %s -> достигнут лимит длины имени. Имя будет усечено до 99 символов\n\n", fname);
                    break;
                }
            c = getchar();
        }
    name[i] = '\0';

    printf("%sВведено слово: %s\n\n", INDENT, name);

    name_trunkate = (char*) malloc(sizeof(char)*(strlen(name)+1));
    strcpy(name_trunkate, name);

    free((void*) name);

    return name_trunkate;
}


char *read_defn_from_console()
{
    char *fname = "read_defn_from_console";

    char c;
    const int MAX_LEN = 1000;
    int i(0);
    char *defn;
    char *defn_trunkate;

    defn = (char*) malloc(sizeof(char)*MAX_LEN);

    c = getchar();
    if (c == '\n' || c == ' ')
        c = getchar();
    
    while (c != '|')
        {
            defn[i] = c;
            i++;
            if (i == (MAX_LEN-1))
                {
                    printf("\nFUNC %s -> достигнут лимит длины определения. Определение будет усечено до 999 символов\n\n", fname);
                    break;
                }
            c = getchar();
        }
    defn[i] = '\0';

    printf("%sВведено определение: %s\n\n", INDENT, defn);

    defn_trunkate = (char*) malloc(sizeof(char)*(strlen(defn)+1));
    strcpy(defn_trunkate, defn);

    free((void*) defn);

    return defn_trunkate;
}