#include "unity.h"
#include "process_text.h"
#include "readwrite.h"
#include "strtbl.h"
#include "editdist.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_count_edit_dist(void)
{
    FILE *input;
    char *test_str1, *test_str2, *test_str3, *test_str4, *test_str5;

    test_str1 = "This is a test string1|";
    test_str2 = "This is a test string1|";

    test_str3 = "This is a test string with differnet words|";
    test_str4 = "";
    test_str5 = "";
    
    TEST_ASSERT_EQUAL_INT(0, count_edit_dist(1, "", "", input, test_str1, test_str2));
    TEST_ASSERT_EQUAL_INT(4, count_edit_dist(1, "", "", input, test_str1, test_str3));
    TEST_ASSERT_EQUAL_INT(5, count_edit_dist(1, "", "", input, test_str1, test_str4));
    TEST_ASSERT_EQUAL_INT(0, count_edit_dist(1, "", "", input, test_str4, test_str5));
}