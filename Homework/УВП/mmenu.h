#include <locale.h>
#include <conio.h>
#include <Windows.h>
#include "miohandler.h"

#define INDENT "\t"


void user_input_reader(int *selection_holder, char **options, int options_num, char *menu_level);
void menu_main();
void menu_creation();
void menu_create_from_console();
void menu_open();
void menu_manage_dict();
void menu_console_print();