/**
 * @author Alex Brandt
 * @copyright MIT
 * @date 2014
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <check.h>
#include <stdlib.h>

#include "../../../lib/cf-bindings/account.h"

#include "../../../lib/cf-bindings/container.h"
#include "../../../lib/cf-bindings/container.c"

/**
 * @test MAX_NUM_CONTAINERS 500000
 */
START_TEST(test_max_num_containers)
{
    ck_assert_int_eq(MAX_NUM_CONTAINERS, 500000);
}
END_TEST

/**
 * @test container_create—prepares and populates a Container.
 */
START_TEST(test_container_create)
{
    Container * container = container_create();
    container_free(container);
}
END_TEST

Suite * container_suite(void) {
    Suite * suite = suite_create("Container");

    TCase * tc = tcase_create("MAX_NUM_CONTAINERS");
    tcase_add_test(tc, test_max_num_containers);
    suite_add_tcase(suite, tc);

    tc = tcase_create("Create");
    tcase_add_test(tc, test_container_create);
    suite_add_tcase(suite, tc);

    return suite;
}

int main() {
    int number_failed;

    Suite * suite = container_suite();
    SRunner * suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_ENV);

    number_failed = srunner_ntests_failed(suite_runner);

    srunner_free(suite_runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
