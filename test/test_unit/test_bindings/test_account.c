/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <check.h>
#include <stdlib.h>

#include "bindings/account.h"

START_TEST (test_account_create)
{
	fail_if(account_create() == NULL, "Account struct not initialized!");

#if 0
	/**
	 * @todo Add tests like the following as conditions are reported as not
	 *       being handled correctly.
	 */
	errno = 0;
	if (account_create() == NULL) {
		fail_unless(errno == ENOMEM, "Couldn't allocate memory");
	}
#endif
}
END_TEST

START_TEST (test_account_free)
{
	account * a = account_create(); /*!< @todo Mock account create or hand code? */

	account_free(a);

	fail_unless(a == NULL, "Memory not properly freed");
}
END_TEST

START_TEST (test_get_account_property)
{
	account * a = account_create();

	/**
	 * @todo Mock things …
	 */
	fail_unless(get_account_property(a, CONTAINER_COUNT, FALSE) == 3, "Incorrect container account returned!");

	fail_unless(get_account_property(a, CONTAINER_COUNT, TRUE) == 3, "Incorrect container account returned!");
	/**
	 * @todo Check accesses to request function.
	 */

	account_free(a);
}
END_TEST

Suite * account_suite_create(void) {
	Suite * s = suite_create("account");
	TCase * tc;

	tc = tcase_create("account_create");
	tcase_add_test(tc, test_account_create);
	suite_add_tcase(s, tc);

	tc = tcase_create("account_free");
	tcase_add_test(tc, test_account_free);
	suite_add_tcase(s, tc);

	tc = tcase_create("get_account_property");
	tcase_add_test(tc, test_get_account_property);
	suite_add_tcase(s, tc);

	return s;
}

int main(void) {
	int number_failed;

	Suite * s = account_suite_create();

	SRunner * sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
