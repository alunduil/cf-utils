/**
 * @author Alex Brandt
 * @copyright MIT
 * @date 2014
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_ACCOUNT_H
#define CF_ACCOUNT_H

#define MAX_NUM_CONTAINERS 500000

struct container;

typedef struct account {
	char * username; /*!< Account Username */
	char * api_key; /*!< Account API Key */

	struct container * containers; /*!< Account's Containers */
	unsigned int container_count; /*!< Number of Containers on account */
} Account;

/**
 * @brief Allocate an Account.
 *
 * Allocates memory for an Account and returns a pointer to this structure.  The
 * memory should be deallocated by a matching call to account_free.
 *
 * @param[in] username Username for the Account
 * @param[in] api_key  API Key for the Account
 *
 * @return Account *
 *
 * @see account_free
 */
Account * account_create(char * username, char * api_key);

/**
 * @brief Deallocate an Account.
 *
 * Frees all memory for an Account including property memory.
 *
 * @param[in,out] account Pointer to the Account being freed will be NULL upon
 *                        return.
 */
void account_free(Account * account);

#endif
