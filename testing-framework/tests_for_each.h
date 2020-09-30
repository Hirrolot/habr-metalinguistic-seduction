#ifndef TESTING_FRAMEWORK_TESTS_AUX_H
#define TESTING_FRAMEWORK_TESTS_AUX_H

#include "aux.h"

#define TESTS_FOR_EACH(op, tests)     TESTS_FOR_EACH_AUX(op, tests end() end())
#define TESTS_FOR_EACH_AUX(op, tests) TESTS_FOR_EACH_0(op, TESTS_HEAD(tests), TESTS_TAIL(tests))
#define TESTS_FOR_EACH_0(op, head, tail)                                                           \
    IF(TESTS_FOR_EACH_IS_END(head),                                                                \
       EMPTY(),                                                                                    \
       TESTS_FOR_EACH_CALL_OP(op, head) TESTS_FOR_EACH_1(op, TESTS_HEAD(tail), TESTS_TAIL(tail)))
#define TESTS_FOR_EACH_1(op, head, tail)                                                           \
    IF(TESTS_FOR_EACH_IS_END(head),                                                                \
       EMPTY(),                                                                                    \
       TESTS_FOR_EACH_CALL_OP(op, head) TESTS_FOR_EACH_3(op, TESTS_HEAD(tail), TESTS_TAIL(tail)))
#define TESTS_FOR_EACH_2(op, head, tail)                                                           \
    IF(TESTS_FOR_EACH_IS_END(head),                                                                \
       EMPTY(),                                                                                    \
       TESTS_FOR_EACH_CALL_OP(op, head) TESTS_FOR_EACH_3(op, TESTS_HEAD(tail), TESTS_TAIL(tail)))
#define TESTS_FOR_EACH_3(op, head, tail)                                                           \
    IF(TESTS_FOR_EACH_IS_END(head),                                                                \
       EMPTY(),                                                                                    \
       TESTS_FOR_EACH_CALL_OP(op, head)                                                            \
           TESTS_FOR_EACH_4_LIMIT_REACHED(op, TESTS_HEAD(tail), TESTS_TAIL(tail)))

#define TESTS_FOR_EACH_CALL_OP(op, test) op(TEST_NAME(test), TEST_BODY(test))

#define TEST_NAME(test)                    MATCH(TEST_NAME_AUX, test)
#define TEST_NAME_AUX_test(test_name, ...) test_name

#define TEST_BODY(test)                     MATCH(TEST_BODY_AUX, test)
#define TEST_BODY_AUX_test(_test_name, ...) __VA_ARGS__

#define TESTS_FOR_EACH_IS_END(test)                 MATCH(TESTS_FOR_EACH_IS_END, test)
#define TESTS_FOR_EACH_IS_END_test(_test_name, ...) 0
#define TESTS_FOR_EACH_IS_END_end()                 1

#define TESTS_HEAD(tests)                      TESTS_HEAD_REMOVE_TAIL(MATCH(TESTS_HEAD_AUX, tests))
#define TESTS_HEAD_AUX_test(test_name, ...)    test(test_name, __VA_ARGS__),
#define TESTS_HEAD_AUX_end()                   end(),
#define TESTS_HEAD_REMOVE_TAIL(...)            TESTS_HEAD_REMOVE_TAIL_AUX(__VA_ARGS__)
#define TESTS_HEAD_REMOVE_TAIL_AUX(head, tail) head

#define TESTS_TAIL(tests)                    MATCH(TESTS_TAIL_AUX, tests)
#define TESTS_TAIL_AUX_test(_test_name, ...) EMPTY()
#define TESTS_TAIL_AUX_end()                 EMPTY()

#endif // TESTING_FRAMEWORK_TESTS_AUX_H