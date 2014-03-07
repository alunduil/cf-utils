/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>

#include "actions.h"

HTTPResponse* http(const http_request* req)
{
	char * url = req->url;

	HTTPResponse * resp = NULL;

	free(url); /** @todo STUB! */

	return resp;
}
