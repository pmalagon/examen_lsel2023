#include "unity.h"

#include "snake.h"
#include "mock_snake_random.h"
#include "mock_snake_display.h"
#include "mock_snake_input.h"
#include "mock_snake_time.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_snake_getLimitReturnsLimitValues(void)
{
    snake_game_t s;

    int x, y;
    x = -1;
    y = -1;

    snake_get_limits(&s, &x, &y);
    TEST_ASSERT_FALSE (x == -1);
    TEST_ASSERT_FALSE (y == -1);

    x = -2;
    y = -2;
    snake_get_limits(&s, &x, &y);
    TEST_ASSERT_FALSE (x == -2);
    TEST_ASSERT_FALSE (y == -2);
}

void test_snake_limitBelow4IsInvalid(void)
{
    snake_game_t s;

    int result = 0;
    
    result = snake_init(&s, 7, 3);
    TEST_ASSERT_EQUAL (0, result);

    result = snake_init(&s, 3, 7);
    TEST_ASSERT_EQUAL (0, result);

}

void test_snake_initFunctionIsExecutedInOrder(void)
{
    snake_game_t s;

    snake_display_init_ExpectAnyArgsAndReturn(1);
    snake_time_init_ExpectAnyArgsAndReturn(1);
    snake_random_init_ExpectAnyArgsAndReturn(1);
    snake_input_init_ExpectAnyArgsAndReturn(1);

    int result = snake_init(&s, 8, 8);
    TEST_ASSERT_EQUAL (1, result);
}

void test_snake_validLimitIsSet(void)
{
    snake_game_t s;

    snake_display_init_IgnoreAndReturn(1);
    snake_time_init_IgnoreAndReturn(1);
    snake_random_init_IgnoreAndReturn(1);
    snake_input_init_IgnoreAndReturn(1);

    int result = snake_init(&s, 6, 8);
    TEST_ASSERT_EQUAL (1, result);

    int x, y;
    snake_get_limits(&s, &x, &y);
    TEST_ASSERT_EQUAL(6, x);
    TEST_ASSERT_EQUAL(8, y);

    result = snake_init(&s, 14, 16);
    TEST_ASSERT_EQUAL (1, result);

    snake_get_limits(&s, &x, &y);
    TEST_ASSERT_EQUAL(14, x);
    TEST_ASSERT_EQUAL(16, y);
}

void test_snake_getHeadReturnsCurrentHead(void)
{
    snake_game_t s;
    int x, y;

    snake_display_init_IgnoreAndReturn(1);
    snake_time_init_IgnoreAndReturn(1);
    snake_random_init_IgnoreAndReturn(1);
    snake_input_init_IgnoreAndReturn(1);

    snake_init(&s, 4, 4);
    snake_set_head(&s, 1, 2);
    snake_get_head(&s, &x, &y);

    TEST_ASSERT_EQUAL(1, x);
    TEST_ASSERT_EQUAL(2, y);

}

void test_snake_checkLowerCollisions(void)
{
    snake_game_t s;
    int result;
    
    snake_display_init_IgnoreAndReturn(1);
    snake_time_init_IgnoreAndReturn(1);
    snake_random_init_IgnoreAndReturn(1);
    snake_input_init_IgnoreAndReturn(1);

    snake_init(&s, 4, 4);

    snake_set_head(&s, 0, 0);
    result = snake_check_collision(&s);
    TEST_ASSERT_EQUAL(0, result);

    snake_set_head(&s, -1, 0);
    result = snake_check_collision(&s);
    TEST_ASSERT_EQUAL(1, result);    

    snake_set_head(&s, 0, -1);
    result = snake_check_collision(&s);
    TEST_ASSERT_EQUAL(1, result);    

}

void test_snake_checkUpperCollisions(void)
{
    snake_game_t s;
    int result;
    
    snake_display_init_IgnoreAndReturn(1);
    snake_time_init_IgnoreAndReturn(1);
    snake_random_init_IgnoreAndReturn(1);
    snake_input_init_IgnoreAndReturn(1);

    snake_init(&s, 4, 4);

    snake_set_head(&s, 3, 3);
    result = snake_check_collision(&s);
    TEST_ASSERT_EQUAL(0, result);

    snake_set_head(&s, 4, 3);
    result = snake_check_collision(&s);
    TEST_ASSERT_EQUAL(1, result);    

    snake_set_head(&s, 3, 4);
    result = snake_check_collision(&s);
    TEST_ASSERT_EQUAL(1, result);    
}

void test_snake_getLengthIsOneAfterHeadSet(void)
{
    snake_game_t s;
    int result = 0;

    snake_display_init_IgnoreAndReturn(1);
    snake_time_init_IgnoreAndReturn(1);
    snake_random_init_IgnoreAndReturn(1);
    snake_input_init_IgnoreAndReturn(1);

    snake_init(&s, 4, 4);

    snake_set_head(&s, 2, 2);
    result = snake_get_snake_length(&s);
    result = 1;
    TEST_ASSERT_EQUAL(1, result);
}

