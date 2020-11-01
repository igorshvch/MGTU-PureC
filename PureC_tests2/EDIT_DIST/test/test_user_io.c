#include "unity.h"
#include "user_io.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_verify_not_too_long_WIN(void)
{
    int i = 0;
    char test_str1[] = "too_small_string";
    char test_str2[MAX_PATH]; //MAX_PATH = 260

    for (i=0; i<MAX_PATH+1; i++)
        test_str2[i] = 'c';
    
    TEST_ASSERT_EQUAL_INT(0, verify_not_too_long_WIN(test_str1));
    TEST_ASSERT_EQUAL_INT(1, verify_not_too_long_WIN(test_str2));
}
/*
void test_verify_not_too_long_WIN2(void)
{
    TEST_ASSERT_EQUAL_INT(1, verify_not_too_long_WIN("Some_test"));
}

void test_verify_not_too_long_WIN3(void)
{

    TEST_ASSERT_EQUAL_INT(0, verify_not_too_long_WIN(test_str));
}

void test_verify_not_too_long_WIN4(void)
{
    TEST_ASSERT_EQUAL_INT(1, verify_not_too_long_WIN("Some_test_too_long_to_use_as_a_proper_file_name. Actually, let's try to use some ristricted symbols)))1234123412341324123413241324132413241324132413241324123413241341324123413241234132413241324123412341324123412341324123412341234123409465049504590495640596405964506945609450694506940596450964056945096406945069"));
}
*/