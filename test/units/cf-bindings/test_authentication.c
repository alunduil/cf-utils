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
#include "../../../lib/uhttpc/response.h"

#include "../../fixtures/cf-bindings/fixtures_authentication.h"

/**
 * @test authenticate—obtain a login token given a username and apikey.
 *
 * @todo Normal Statuses:
 *       * 200
 *       * 203
 *
 * @todo Error Statuses:
 *       * 400—Bad Request
 *       * 401—Unauthorized
 *       * 403—User Disabled
 *       * 500—Auth Fault
 *       * 503—Service Unavailable
 */
START_TEST(test_authentication)
{
    /**
     * @todo Add fixture support to handle the test matrix.
     * Craft an expected response for the mock HTTP call.
     */
    HTTPResponse * mock_response = http_response_create();
    Account * account = account_create();
	Account * check = authenticate(account, "username", "apikey");

	ck_assert_ptr_ne(check, NULL);
	ck_assert_str_eq(account->token, "aeb90dd1-34e0-4ea1-a081-6145687a924b");

    /** @todo Check that https://identity.api.rackspacecloud.com/v2.0/tokens is identity endpoint. */
    /** @todo Verify POST method is used. */

    account_free(account);
}
END_TEST

Suite * authentication_suite(void) {
	Suite * suite = suite_create("Test Authentication");

	TCase * tc = tcase_create("Authenticate");
	tcase_add_test(tc, test_authentication);
	suite_add_tcase(suite, tc);

	return suite;
}

int main() {
	int number_failed;

	Suite * suite = authentication_suite();
	SRunner * suite_runner = srunner_create(suite);

	srunner_run_all(suite_runner, CK_NORMAL);

	number_failed = srunner_ntests_failed(suite_runner);

	srunner_free(suite_runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
