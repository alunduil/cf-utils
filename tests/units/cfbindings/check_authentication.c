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

#include "../../../lib/cfbindings/account.h"
#include "../../../lib/cfbindings/account.c"

/**
 * @test authenticate—obtain a login token given a username and apikey.
 */
START_TEST(test_authentication)
{
    Account * account = account_create("username", "apikey");
    Account * check = authenticate(account);

    ck_assert_ptr_ne(check, NULL);
    ck_assert_str_eq(account->token, "aeb90dd1-34e0-4ea1-a081-6145687a924b");

    account_free(account);
}
END_TEST

Suite * authentication_suite(void) {
    Suite * suite = suite_create("Authentication");

    TCase * tc = tcase_create("Authenticate");
    tcase_add_test(tc, test_authentication);
    suite_add_tcase(suite, tc);

    return suite;
}

int main() {
    int number_failed;

    Suite * suite = authentication_suite();
    SRunner * suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_ENV);

    number_failed = srunner_ntests_failed(suite_runner);

    srunner_free(suite_runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
