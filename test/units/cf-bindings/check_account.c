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

#include "check_account.h"

#include "../../../lib/cf-bindings/account.h"

/**
 * @test account_create—produces a properly initialized account.
 */
START_TEST(test_account_create)
{
	Account * account = account_create(NULL, NULL);

	ck_assert_ptr_eq(account->username, NULL);
	ck_assert_ptr_eq(account->api_key, NULL);
	ck_assert_ptr_eq(account->containers, NULL);

    account_free(account);
}
END_TEST

/**
 * @test account_create—produces a properly initialized account.
 */
START_TEST(test_account_create_parameterized)
{
	Account * account = account_create("username", "1709c3ebba4549f9a4719ef3b2876a7c");

	ck_assert_str_eq(account->username, "username");
	ck_assert_str_eq(account->api_key, "1709c3ebba4549f9a4719ef3b2876a7c");
	ck_assert_ptr_eq(account->containers, NULL);

    account_free(account);
}
END_TEST

Suite * account_suite(void) {
	Suite * suite = suite_create("Account");
	TCase * tc = tcase_create("Create");

	tcase_add_test(tc, test_account_create);
	tcase_add_test(tc, test_account_create_parameterized);

	suite_add_tcase(suite, tc);

	return suite;
}

int main() {
	int number_failed;

	Suite * suite = account_suite();
	SRunner * suite_runner = srunner_create(suite);

	srunner_run_all(suite_runner, CK_ENV);

	number_failed = srunner_ntests_failed(suite_runner);

	srunner_free(suite_runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
