//#include "user_io.h"

#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "unity_fixture.h"

TEST(printf, NoFormatOperations)
{
    char output[5];
    TEST_ASSERT_EQUAL_INT(3, printf(output, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", output);
}


TEST_GROUP_RUNNER(printf)
{
    RUN_TEST_CASE(printf, NoFormatOperations);
}


static void RunAllTests(void)
{
    RUN_TEST_GROUP(printf);
}

int main(int argc, char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}

/*
#include "Unity_compact/unity_fixture.h"

TEST_GROUP(PureC_tests);

TEST_SETUP(PureC_tests)
{

}

TEST_TEAR_DOWN(PureC_tests)
{

}

TEST(PureC_tests, FirstTest)
{
    TEST_FAIL_MESSAGE("Start here");    
}

TEST_GROUP_RUNNER(PureC_tests)
{
    RUN_TEST_CASE(PureC_tests, FirstTest);
}
*/