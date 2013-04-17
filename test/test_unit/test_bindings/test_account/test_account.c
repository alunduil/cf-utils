/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <check.h>
#include <stdlib.h>
#include <errno.h>

#include "test_account_creation.h"

START_TEST ( test_get_account_property ) {
    Account * a = account_create();

    /**
     * @todo Mock things …
     */

    fail_unless ( _get_account_property ( a, _CONTAINER_COUNT, 1 ) == 3, "Incorrect container account returned!" );

    fail_unless ( _get_account_property ( a, _CONTAINER_COUNT, 0 ) == 3, "Incorrect container account returned!" );

    /**
     * @todo Check accesses to request function.
     */

    account_free ( a );
}
END_TEST

Suite * account_suite_create ( void ) {
    Suite * s = suite_create ( "account" );
    TCase * tc;

    tc = tcase_create ( "account_create_success" );
    tcase_add_test ( tc, test_account_create_success );
    suite_add_tcase ( s, tc );

    tc = tcase_create ( "account_create_failure" );
    tcase_add_test ( tc, test_account_create_failure );
    suite_add_tcase ( s, tc );

    tc = tcase_create ( "account_free" );
    tcase_add_test ( tc, test_account_free );
    suite_add_tcase ( s, tc );

    tc = tcase_create ( "get_account_property" );
    tcase_add_test ( tc, test_get_account_property );
    suite_add_tcase ( s, tc );

    return s;
}

int main ( void ) {
    int number_failed;

    Suite * s = account_suite_create();

    SRunner * sr = srunner_create ( s );

    srunner_run_all ( sr, CK_NORMAL );
    number_failed = srunner_ntests_failed ( sr );
    srunner_free ( sr );

    return ( number_failed == 0 ) ? EXIT_SUCCESS : EXIT_FAILURE;
}
