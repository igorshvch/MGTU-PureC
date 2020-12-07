#include "unity.h"
#include "sys_test_edit.h"
#include "cons_interface.h"
#include "process_text.h"
#include "readwrite.h"
#include "strtbl.h"
#include "editdist.h"
#include "cons_interface.h"
#include "user_input_check.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_global_test(void)
{
    char *str;

    char stream1[] = "This is a test string1|";
    char stream2[] = "This is a test string2|";

    str = global_test(stream1, stream2);

    TEST_MESSAGE("First print");
    TEST_MESSAGE(str);

    TEST_ASSERT_EQUAL_STRING("editorial distance equals to 1\n", str);
}