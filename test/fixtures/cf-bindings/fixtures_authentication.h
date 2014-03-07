/**
 * @author Alex Brandt
 * @copyright MIT
 * @date 2014
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_TEST_FIXTURES_AUTHENTICATION_H
#define CF_TEST_FIXTURES_AUTHENTICATION_H

#include "../../../lib/uhttpc/request.h"
#include "../../../lib/uhttpc/response.h"

typedef struct {
	HTTPRequest * req; /*!< HTTP Request */
	HTTPResponse * resp; /*!< HTTP Response */

	FixtureItem * next; /*!< Next Item in List */
} FixtureItem;

/**
 * @brief Create authentication fixtures.
 *
 * @return FixtureItem * — beginning of a linked list.
 */
FixtureItem * fixtures_create();

/**
 * @brief Free the entire list of fixtures.
 *
 * @param[in] fixtures First item in a list of FixtureItem *.
 */
void fixtures_free(FixtureItem * fixtures);

#endif
