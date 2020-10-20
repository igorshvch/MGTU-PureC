#include "user_io.h"

int main()
{
    char *str1, *str2;
    str1 = "0";
    str2 = "0";
    
    console_interface(str1, str2, process_input_string);
}