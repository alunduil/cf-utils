/**
 * @author Alex Brandt
 * @copyright MIT
 * @date 2014
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>
#include <string.h>

#include "account.h"

Account * account_create(char * username, char * api_key) {
	Account * account = (Account *) malloc(sizeof(Account));

	if (username != NULL) {
		account->username = (char *) malloc(sizeof(char) * strlen(username) + 1);
		strcpy(account->username, username);
	}
	else
	{
		account->username = username;
	}

	if (api_key != NULL) {
		account->api_key = (char *) malloc(sizeof(char) * strlen(api_key) + 1);
		strcpy(account->api_key, api_key);
	}
	else
	{
		account->api_key = api_key;
	}

	account->containers = NULL;
	account->container_count = 0;

	return account;
}

void account_free(Account * account) {
	free(account->username);
	free(account->api_key);
	free(account->containers);

	free(account);
}
