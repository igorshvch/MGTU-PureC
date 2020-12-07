#include "unity.h"
#include "readwrite.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_read_from_file(void)
{
    FILE *input;
    char *test_str, *read_str;

    test_str = "This is a test string|";
    
    TEST_ASSERT_EQUAL_STRING(test_str, read_from_file(1, input, test_str, ""));
}