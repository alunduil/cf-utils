/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_TEST_UNIT_BINDINGS_ACCOUNT_CREATION
#define CF_TEST_UNIT_BINDINGS_ACCOUNT_CREATION

#include <check.h>
#include <stdlib.h>
#include <errno.h>

#include "../../../../lib/cf-bindings/account.h"

START_TEST ( test_account_create_success ) {
	errno = 0;

	Account * a = account_create();

	if ( errno != 0 )
		fail ( "Error status changed during account_create call!" );

	fail_if ( a == NULL, "Account struct not initialized!" );
}
END_TEST

START_TEST ( test_account_create_failure ) {
	#if 0
	/**
	 * @todo Add tests like the following as conditions are reported as not
	 *       being handled correctly.
	 */
	errno = 0;
	if ( account_create() == NULL ) {
		fail_unless ( errno == ENOMEM, "Couldn't allocate memory" );
}
#endif
}
END_TEST

START_TEST ( test_account_free ) {
	Account * a = account_create(); /*!< @todo Mock account create or hand code? */

	account_free ( a );

	fail_unless ( a == NULL, "Memory not properly freed" );
}
END_TEST

#endif
