/**
 * @copyright 2014
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <check.h>
#include <stdlib.h>

#include "../../../lib/cf-bindings/container.h"

/**
 * @test MAX_CONTAINER_NUM 500000
 *
 * Following the specification, there should be no more than 500,000 containers
 * on a particular account.
 *
 * @todo Determine if this should be defined here or test_account.c.
 */
START_TEST(test_max_container_num)
{
    ck_assert_int_eq(MAX_CONTAINER_NUM, 500000);
}
END_TEST

/**
 * @test MAX_CONTAINER_NAME_LENGTH 256
 *
 * Following the specification, there should be no more than 256 bytes in a
 * container's name.
 */
START_TEST(test_max_container_name_length)
{
    ck_assert_int_eq(MAX_CONTAINER_NAME_LENGTH, 256);
}
END_TEST

/**
 * @test container_create—prepares and populates a Container.
 */
START_TEST(test_container_create)
{
    Container * container = container_create();
	ck_assert_str_eq(container->name, "");

	/** @todo merge these elements? */
	ck_assert(!container->cdn_enabled);
	ck_assert_str_eq(container->cdn_url, "");
	ck_assert_int_eq(container->cdn_ttl, 0);
    container_free(container);
}
END_TEST

/**
 * @test container_encode_name—encodes the container's name
 *
 * A container's name cannot exceed 256 bytes in length after URL-encoding and
 * cannot contain a '/' character.
 */
START_TEST(test_container_encode_name)
{
    /** @todo Add fixture support. */
	char name[MAX_CONTAINER_NAME_LENGTH + 1];

	Container * container = container_create();
	strncpy(container->name, "Course Docs", MAX_CONTAINER_NAME_LENGTH + 1);
	ck_assert_str_eq(container_encode_name(container, name), "Course%20Docs");

	/**
	 * @todo Add error tests…
	 *
	 * * Course/Docs—Invalid character.
	 * * Too long of a string.
	 */

	container_free(container);
}
END_TEST

Suite * container_suite(void) {
	Suite * suite = suite_create("Test Container");

	TCase * tc = tcase_create("MAX_CONTAINER_NUM");
	tcase_add_test(tc, test_max_container_num);
	suite_add_tcase(suite, tc);

	tc = tcase_create("MAX_CONTAINER_NAME_LENGTH");
	tcase_add_test(tc, test_max_container_name_length);
	suite_add_tcase(suite, tc);

	tc = tcase_create("Create");
	tcase_add_test(tc, test_container_create);
	suite_add_tcase(suite, tc);

	tc = tcase_create("Encode Name");
	tcase_add_test(tc, test_container_encode_name);
	suite_add_tcase(suite, tc);

	return suite;
}

int main() {
	int number_failed;

	Suite * suite = container_suite();
	SRunner * suite_runner = srunner_create(suite);

	srunner_run_all(suite_runner, CK_NORMAL);

	number_failed = srunner_ntests_failed(suite_runner);

	srunner_free(suite_runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
